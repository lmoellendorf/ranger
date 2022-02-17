/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Simplified EncoderOnBoardMotor Movements
 *
 * @details
 */

#include "LmEncoderOnBoardMotor.h"
#include "LmTimer.h"
#include <math.h>
#include <float.h>

MeEncoderOnBoard EncoderOnBoardMotor::encoder1(SLOT1);
MeEncoderOnBoard EncoderOnBoardMotor::encoder2(SLOT2);
bool EncoderOnBoardMotor::pos_reached[] = { false, false };
bool EncoderOnBoardMotor::synced = false;

void EncoderOnBoardMotor::IsrProcessEncoder1(void)
{
	if (digitalRead(encoder1.getPortB()) == 0)
		encoder1.pulsePosMinus();
	else
		encoder1.pulsePosPlus();
}

void EncoderOnBoardMotor::IsrProcessEncoder2(void)
{
	if (digitalRead(encoder2.getPortB()) == 0)
		encoder2.pulsePosMinus();
	else
		encoder2.pulsePosPlus();
}

EncoderOnBoardMotor::EncoderOnBoardMotor(int slot, float ratio) : slot(slot)
{
	//Set PWM 8KHz
	TCCR1A = _BV(WGM10);
	TCCR1B = _BV(CS11) | _BV(WGM12);

	TCCR2A = _BV(WGM21) | _BV(WGM20);
	TCCR2B = _BV(CS21);

	//Encoder.reset(slot);
	switch (slot) {
	case SLOT1:
		attachInterrupt(encoder1.getIntNum(), IsrProcessEncoder1, RISING);
		encoder1.setPulse(9);
		encoder1.setRatio(ratio);
		encoder1.setPosPid(1.8, 0, 1.2);
		encoder1.setSpeedPid(0.18, 0, 0);
		break;

	case SLOT2:

	/** fall through */
	default:
		attachInterrupt(encoder2.getIntNum(), IsrProcessEncoder2, RISING);
		encoder2.setPulse(9);
		encoder2.setRatio(ratio);
		encoder2.setPosPid(1.8, 0, 1.2);
		encoder2.setSpeedPid(0.18, 0, 0);
		break;
	}
}

EncoderOnBoardMotor::EncoderOnBoardMotor(int slot) : slot(slot)
{
	EncoderOnBoardMotor(slot, 39.267);
}

void EncoderOnBoardMotor::PositionReached(int16_t slot, int16_t ext_id)
{
	int i = (slot == SLOT1 ? 0 : 1);

	pos_reached[i] = true;
}

bool EncoderOnBoardMotor::IsPositionReached(int16_t slot)
{
	int i = (slot == SLOT1 ? 0 : 1);
	bool ret;

	noInterrupts();
	ret = pos_reached[i];
	interrupts();
	return ret;
}

void EncoderOnBoardMotor::ResetPositionReached(int16_t slot)
{
	int i = (slot == SLOT1 ? 0 : 1);

	noInterrupts();
	pos_reached[i] = false;
	interrupts();
}

bool EncoderOnBoardMotor::ArePositionsReached(void)
{
	bool ret;

	noInterrupts();
	ret = pos_reached[0] && pos_reached[1];
	interrupts();
	return ret;
}

void EncoderOnBoardMotor::SetSynced(bool on)
{
	noInterrupts();
	synced = on;
	interrupts();
}

bool EncoderOnBoardMotor::GetSynced(void)
{
	bool ret;

	noInterrupts();
	ret = synced;
	interrupts();
	return ret;
}

void EncoderOnBoardMotor::syncCurrentSpeed(void)
{
	float speed;

	if (GetSynced()) {
		speed = encoder1.getCurrentSpeed();

		if (encoder1.distanceToGo() > encoder2.distanceToGo()) {
			/* increment without overflow */
			speed += speed <= FLT_MAX - 1 ? 1 : 0;
			encoder1.setCurrentSpeed(speed);
		} else if (encoder1.distanceToGo() < encoder2.distanceToGo()) {
			/* decrement without becoming negative */
			speed -= speed >= 1 ? 1 : 0;
			encoder1.setCurrentSpeed(speed--);
		}
	}
}

void EncoderOnBoardMotor::Loop1(void)
{
	if (!pos_reached[0]) {
		syncCurrentSpeed();
		encoder1.loop();
	} else
		encoder1.runSpeed(0);
}

void EncoderOnBoardMotor::Loop2(void)
{
	if (!pos_reached[1]) {
		syncCurrentSpeed();
		encoder2.loop();
	} else
		encoder2.runSpeed(0);
}

void EncoderOnBoardMotor::Rotate(long position, float speed)
{
	return Rotate(position, speed, false, false);
}

void EncoderOnBoardMotor::Rotate(long position, float speed, bool block)
{
	return Rotate(position, speed, block, false);
}

void EncoderOnBoardMotor::Rotate(long position, float speed, bool block,
				 bool sync)
{
	int slot = EncoderOnBoardMotor::slot;
	int i = (slot == SLOT1 ? 0 : 1);
	MeEncoderOnBoard *encoder = slot == SLOT1 ? &encoder1 : &encoder2;

	if (block)
		Timer::UnregisterCallback(i ? Loop2 : Loop1);

	else
		Timer::RegisterCallback(i ? Loop2 : Loop1);

	SetSynced(sync);
	ResetPositionReached(i);
	encoder->move(position, speed, NULL, PositionReached);

	if (block) {
		while (!IsPositionReached(i)) {
			syncCurrentSpeed();
			encoder->loop();
		}

		if (GetSynced()) {
			encoder1.runSpeed(0);
			encoder2.runSpeed(0);
		} else
			encoder->runSpeed(0);
	}
}

void EncoderOnBoardMotor::Forward(float speed)
{
	int slot = EncoderOnBoardMotor::slot;
	int i = (slot == SLOT1 ? 0 : 1);
	MeEncoderOnBoard *encoder = slot == SLOT1 ? &encoder1 : &encoder2;

	ResetPositionReached(i);
	Timer::RegisterCallback(i ? Loop2 : Loop1);
	encoder->runSpeed(speed);
}

void EncoderOnBoardMotor::Stop(void)
{
	MeEncoderOnBoard *encoder = slot == SLOT1 ? &encoder1 : &encoder2;

	encoder->runSpeed(0);
}
