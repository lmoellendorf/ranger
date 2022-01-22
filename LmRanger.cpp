/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Simplified Ranger Movements
 *
 * @details
 */

#include "LmRanger.h"


MeEncoderOnBoard Ranger::_EncoderL;
MeEncoderOnBoard Ranger::_EncoderR;
bool Ranger::pos_l_reached = false;
bool Ranger::pos_r_reached = false;

void Ranger::isr_process_encoderL(void)
{
	if (digitalRead(_EncoderL.getPortB()) == 0)
		_EncoderL.pulsePosMinus();
	else
		_EncoderL.pulsePosPlus();
}

void Ranger::isr_process_encoderR(void)
{
	if (digitalRead(_EncoderR.getPortB()) == 0)
		_EncoderR.pulsePosMinus();
	else
		_EncoderR.pulsePosPlus();
}

Ranger::Ranger(int slot_l, int slot_r)
{
	_EncoderL.reset(slot_l);
	_EncoderR.reset(slot_r);
	attachInterrupt(_EncoderL.getIntNum(), isr_process_encoderL, RISING);
	attachInterrupt(_EncoderR.getIntNum(), isr_process_encoderR, RISING);
	//Set PWM 8KHz
	TCCR1A = _BV(WGM10);
	TCCR1B = _BV(CS11) | _BV(WGM12);

	TCCR2A = _BV(WGM21) | _BV(WGM20);
	TCCR2B = _BV(CS21);

	_EncoderL.setPulse(9);
	_EncoderR.setPulse(9);
	_EncoderL.setRatio(39.267);
	_EncoderR.setRatio(39.267);
	_EncoderL.setPosPid(1.8, 0, 1.2);
	_EncoderR.setPosPid(1.8, 0, 1.2);
	_EncoderL.setSpeedPid(0.18, 0, 0);
	_EncoderR.setSpeedPid(0.18, 0, 0);
}

void Ranger::reached_position(int16_t slot, int16_t extID)
{
	if (slot == _EncoderL.getSlotNum())
		pos_l_reached = true;

	if (slot == _EncoderR.getSlotNum())
		pos_r_reached = true;
}


void Ranger::moveTo(long position, float speed)
{
	pos_l_reached = false;
	pos_r_reached = false;
	_EncoderL.move(position, speed, NULL, reached_position);
	_EncoderR.move(-position, speed, NULL, reached_position);

	while (!pos_l_reached || !pos_r_reached) {
		_EncoderL.loop();
		_EncoderR.loop();
	}

	_EncoderL.setMotorPwm(0);
	_EncoderR.setMotorPwm(0);
}
