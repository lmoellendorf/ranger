/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Simplified EncoderOnBoardMotor Movements
 *
 * @details
 */

#include "LmEncoderOnBoardMotor.h"

MeEncoderOnBoard EncoderOnBoardMotor::Encoder1(SLOT1);
MeEncoderOnBoard EncoderOnBoardMotor::Encoder2(SLOT2);
bool EncoderOnBoardMotor::pos_reached[] = { false, false };

void EncoderOnBoardMotor::isr_process_encoder1(void)
{
	if (digitalRead(Encoder1.getPortB()) == 0)
		Encoder1.pulsePosMinus();
	else
		Encoder1.pulsePosPlus();
}

void EncoderOnBoardMotor::isr_process_encoder2(void)
{
	if (digitalRead(Encoder2.getPortB()) == 0)
		Encoder2.pulsePosMinus();
	else
		Encoder2.pulsePosPlus();
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
		attachInterrupt(Encoder1.getIntNum(), isr_process_encoder1, RISING);
		Encoder1.setPulse(9);
		Encoder1.setRatio(39.267);
		Encoder1.setPosPid(1.8, 0, 1.2);
		Encoder1.setSpeedPid(0.18, 0, 0);
		break;

	case SLOT2:

	/** fall through */
	default:
		attachInterrupt(Encoder2.getIntNum(), isr_process_encoder2, RISING);
		Encoder2.setPulse(9);
		Encoder2.setRatio(39.267);
		Encoder2.setPosPid(1.8, 0, 1.2);
		Encoder2.setSpeedPid(0.18, 0, 0);
		break;
	}

}

void EncoderOnBoardMotor::reached_position(int16_t slot, int16_t extID)
{
	int i = slot == SLOT1 ? 0 : SLOT2;

	pos_reached[i] = true;
}


void EncoderOnBoardMotor::move_to(long position, float speed)
{
	int slot = EncoderOnBoardMotor::slot;
	int i = slot == SLOT1 ? 0 : SLOT2;
	MeEncoderOnBoard *encoder = slot == SLOT1 ? &Encoder1 : &Encoder2;

	pos_reached[i] = false;
	encoder->move(position, speed, NULL, reached_position);

	while (!pos_reached[i])
		encoder->loop();

	encoder->setMotorPwm(0);
}
