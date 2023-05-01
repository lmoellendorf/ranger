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

void EncoderOnBoardMotor::isrProcessEncoder1(void)
{
	if (digitalRead(encoder1.getPortB()) == 0)
		encoder1.pulsePosMinus();
	else
		encoder1.pulsePosPlus();
}

void EncoderOnBoardMotor::isrProcessEncoder2(void)
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
		attachInterrupt(encoder1.getIntNum(), isrProcessEncoder1, RISING);
		encoder1.setPulse(9);
		encoder1.setRatio(ratio);
		encoder1.setPosPid(1.8, 0, 1.2);
		encoder1.setSpeedPid(0.18, 0, 0);
		break;

	case SLOT2:

	/** fall through */
	default:
		encoder2.reset(slot);
		attachInterrupt(encoder2.getIntNum(), isrProcessEncoder2, RISING);
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

MeEncoderOnBoard *EncoderOnBoardMotor::slot2Encoder(int slot)
{
	return slot == SLOT1 ? &encoder1 : &encoder2;
}

int EncoderOnBoardMotor::slot2Index(int slot)
{
	return (slot == SLOT1 ? 0 : 1);
}

void EncoderOnBoardMotor::positionReached(int16_t slot, int16_t ext_id)
{
	pos_reached[ext_id] = true;
}

bool EncoderOnBoardMotor::isPositionReached(int16_t slot)
{
	int i = slot2Index(slot);
	bool ret;

	noInterrupts();
	ret = pos_reached[i];
	interrupts();
	return ret;
}

void EncoderOnBoardMotor::resetPositionReached(int16_t slot)
{
	int i = slot2Index(slot);

	noInterrupts();
	pos_reached[i] = false;
	interrupts();
}

bool EncoderOnBoardMotor::arePositionsReached(void)
{
	bool ret;

	noInterrupts();
	ret = pos_reached[0] && pos_reached[1];
	interrupts();
	return ret;
}

void EncoderOnBoardMotor::setSynced(bool on)
{
	noInterrupts();
	synced = on;
	interrupts();
}

bool EncoderOnBoardMotor::getSynced(void)
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

	if (getSynced()) {
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

void EncoderOnBoardMotor::loop(void)
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

void EncoderOnBoardMotor::rotate(long angle, float speed)
{
	return rotate(angle, speed, false, false);
}

void EncoderOnBoardMotor::rotate(long angle, float speed, bool block)
{
	return rotate(angle, speed, block, false);
}

void EncoderOnBoardMotor::rotate(long angle, float speed, bool block,
				 bool sync)
{
	int i = slot2Index(slot);
	MeEncoderOnBoard *encoder = slot2Encoder(slot);

	setSynced(sync);
	Timer::unregisterCallback(loop);
	resetPositionReached(slot);
	encoder->move(angle, speed, i, positionReached);
	Timer::registerCallback(loop);

	if (block) {
		while (!isPositionReached(slot))
			;
	}
}

void EncoderOnBoardMotor::forward(float speed)
{
	int slot = EncoderOnBoardMotor::slot;
	int i = slot2Index(slot);
	MeEncoderOnBoard *encoder = slot2Encoder(slot);

	resetPositionReached(slot);
	Timer::registerCallback(loop);
	encoder->runSpeed(speed);
}

void EncoderOnBoardMotor::stop(void)
{
	MeEncoderOnBoard *encoder = slot2Encoder(slot);

	encoder->runSpeed(0);
}

void EncoderOnBoardMotor::resetTachoCount(void)
{
	MeEncoderOnBoard *encoder = slot2Encoder(slot);

	encoder->setPulsePos(0);
	encoder->updateCurPos();
}

int EncoderOnBoardMotor::getTachoCount(void)
{
	MeEncoderOnBoard *encoder = slot2Encoder(slot);

	return encoder->getCurPos();
}
