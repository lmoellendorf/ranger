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

	switch (slot) {
	case SLOT1:
		encoder1.reset(slot);
		attachInterrupt(encoder1.getIntNum(), IsrProcessEncoder1, RISING);
		encoder1.setPulse(9);
		encoder1.setRatio(ratio);
		encoder1.setPosPid(1.8, 0, 1.2);
		encoder1.setSpeedPid(0.18, 0, 0);
		break;

	case SLOT2:

	/** fall through */
	default:
		encoder2.reset(slot);
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

MeEncoderOnBoard *EncoderOnBoardMotor::Slot2Encoder(int slot)
{
	return slot == SLOT1 ? &encoder1 : &encoder2;
}

int EncoderOnBoardMotor::Slot2Index(int slot)
{
	return (slot == SLOT1 ? 0 : 1);
}

void EncoderOnBoardMotor::PositionReached(int16_t slot, int16_t ext_id)
{
	pos_reached[ext_id] = true;
}

bool EncoderOnBoardMotor::IsPositionReached(int16_t slot)
{
	int i = Slot2Index(slot);
	bool ret;

	noInterrupts();
	ret = pos_reached[i];
	interrupts();
	return ret;
}

void EncoderOnBoardMotor::ResetPositionReached(int16_t slot)
{
	int i = Slot2Index(slot);

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

void EncoderOnBoardMotor::Loop(void)
{
	if (!pos_reached[0]) {
		syncCurrentSpeed();
		encoder1.loop();
	} else
		encoder1.setMotorPwm(0);

	if (!pos_reached[1]) {
		syncCurrentSpeed();
		encoder2.loop();
	} else
		encoder2.setMotorPwm(0);
}

void EncoderOnBoardMotor::Rotate(long angle, float speed)
{
	return Rotate(angle, speed, false, false);
}

void EncoderOnBoardMotor::Rotate(long angle, float speed, bool block)
{
	return Rotate(angle, speed, block, false);
}

void EncoderOnBoardMotor::Rotate(long angle, float speed, bool block,
				 bool sync)
{
	int i = Slot2Index(slot);
	MeEncoderOnBoard *encoder = Slot2Encoder(slot);

	SetSynced(sync);
	Timer::UnregisterCallback(Loop);
	ResetPositionReached(i);
	encoder->move(angle, speed, i, PositionReached);
	Timer::RegisterCallback(Loop);

	if (block) {
		while (!IsPositionReached(i)) {
			;
		}
	}
}

void EncoderOnBoardMotor::Forward(float speed)
{
	int slot = EncoderOnBoardMotor::slot;
	int i = Slot2Index(slot);
	MeEncoderOnBoard *encoder = Slot2Encoder(slot);

	ResetPositionReached(i);
	Timer::RegisterCallback(Loop);
	encoder->runSpeed(speed);
}

void EncoderOnBoardMotor::Stop(void)
{
	MeEncoderOnBoard *encoder = slot == SLOT1 ? &encoder1 : &encoder2;

	encoder->runSpeed(0);
}
