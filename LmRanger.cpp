/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Simplified Ranger Movements
 *
 * @details
 */

#include "LmRanger.h"
#include "LmTimer.h"

MeRGBLed Ranger::led(0, LEDNUM);
volatile float Ranger::j(0), Ranger::f(0), Ranger::k(0);
volatile int t = 0;

Ranger::Ranger(int slot_l = SLOT_L, int slot_r = SLOT_R) :
	MotorL(slot_l), MotorR(slot_r) {}

void Ranger::move_to(long position, float speed)
{
	Ranger::MotorL.MoveTo(position, speed, true);
	Ranger::MotorR.MoveTo(-position, speed, true);
}

void Ranger::color_loop()
{
	uint8_t red = 64 * (1 + sin(t / 2.0 + j / 4.0));
	uint8_t green = 64 * (1 + sin(t / 1.0 + f / 9.0 + 2.1));
	uint8_t blue = 64 * (1 + sin(t / 3.0 + k / 14.0 + 4.2));

	led.setColorAt(t, red, green, blue);
	led.show();
	j += random(1, 6) / 6.0;
	f += random(1, 6) / 6.0;
	k += random(1, 6) / 6.0;
	t++;
	t %= LEDNUM;
}

void Ranger::start_rainbow()
{
	// on-board LED ring, at PORT0 (onboard)
	Ranger::led.setpin(44);
	Timer::register_callback(Ranger::color_loop);
}

void Ranger::stop_rainbow()
{
	Timer::unregister_callback(Ranger::color_loop);
}
