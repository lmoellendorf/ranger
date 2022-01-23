/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Simplified Ranger Movements
 *
 * @details
 */

#include "LmRanger.h"

MeRGBLed Ranger::led(0, LEDNUM);
volatile float Ranger::j(0), Ranger::f(0), Ranger::k(0);

Ranger::Ranger(int slot_l = SLOT_L, int slot_r = SLOT_R) :
	MotorL(slot_l), MotorR(slot_r)
{
	// on-board LED ring, at PORT0 (onboard)
	Ranger::led.setpin(44);
	// enable timer compare interrupt
	TIMSK0 |= (1 << OCIE0A);
}

void Ranger::moveTo(long position, float speed)
{
	Ranger::MotorL.moveTo(position, speed);
	Ranger::MotorR.moveTo(-position, speed);
}

void Ranger::color_loop()
{
	for (uint8_t t = 0; t < LEDNUM; t++) {
		uint8_t red	= 64 * (1 + sin(t / 2.0 + j / 4.0));
		uint8_t green = 64 * (1 + sin(t / 1.0 + f / 9.0 + 2.1));
		uint8_t blue = 64 * (1 + sin(t / 3.0 + k / 14.0 + 4.2));
		led.setColorAt(t, red, green, blue);
	}

	led.show();

	j += random(1, 6) / 6.0;
	f += random(1, 6) / 6.0;
	k += random(1, 6) / 6.0;
}

ISR(TIMER0_COMPA_vect)
{
	Ranger::color_loop();
}
