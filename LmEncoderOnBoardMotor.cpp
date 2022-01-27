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

MeEncoderOnBoard EncoderOnBoardMotor::encoder1(SLOT1);
MeEncoderOnBoard EncoderOnBoardMotor::encoder2(SLOT2);
bool EncoderOnBoardMotor::pos_reached[] = { false, false };

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

EncoderOnBoardMotor::EncoderOnBoardMotor(int slot) : slot(slot)
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
		encoder1.setRatio(39.267);
		encoder1.setPosPid(1.8, 0, 1.2);
		encoder1.setSpeedPid(0.18, 0, 0);
		break;

	case SLOT2:

	/** fall through */
	default:
		attachInterrupt(encoder2.getIntNum(), IsrProcessEncoder2, RISING);
		encoder2.setPulse(9);
		encoder2.setRatio(39.267);
		encoder2.setPosPid(1.8, 0, 1.2);
		encoder2.setSpeedPid(0.18, 0, 0);
		break;
	}
}

void EncoderOnBoardMotor::PositionReached(int16_t slot, int16_t ext_id)
{
	int i = slot == SLOT1 ? 0 : SLOT2;

	pos_reached[i] = true;
}

void EncoderOnBoardMotor::Loop(void)
{
	MeEncoderOnBoard *encoder;

	for (int slot; slot < 2; slot++) {
		encoder = slot == SLOT1 ? &encoder1 : &encoder2;

		if (!pos_reached[slot])
			encoder->loop();
		else
			encoder->setMotorPwm(0);
	}
}

void EncoderOnBoardMotor::LoopSynced(void)
{
	long pos1, pos2;

	pos1 = encoder1.distanceToGo();
	pos2 = encoder2.distanceToGo();
	pos1 = labs(pos1);
	pos2 = labs(pos2);

	if (pos_reached[SLOT1] && pos_reached[SLOT2]) {
		encoder1.setMotorPwm(0);
		encoder2.setMotorPwm(0);
		return;
	}

	if (pos1 == pos2) {
		encoder1.loop();
		encoder2.loop();
		return;
	}

	if (pos1 < pos2) {
		encoder2.loop();
		return;
	}

	if (pos1 > pos2) {
		encoder1.loop();
		return;
	}
}

void EncoderOnBoardMotor::MoveTo(long position, float speed)
{
	return MoveTo(position, speed, false);
}

void EncoderOnBoardMotor::MoveTo(long position, float speed, bool sync)
{
	int slot = EncoderOnBoardMotor::slot;
	int i = slot == SLOT1 ? 0 : SLOT2;
	MeEncoderOnBoard *encoder = slot == SLOT1 ? &encoder1 : &encoder2;

	if (sync)
		Timer::register_callback(LoopSynced);
	else
		Timer::register_callback(Loop);

	pos_reached[i] = false;
	encoder->move(position, speed, NULL, PositionReached);
}
