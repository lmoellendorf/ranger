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
	motor_l(slot_l), motor_r(slot_r) {}

void Ranger::MoveTo(long position, float speed)
{
	Ranger::motor_l.MoveTo(position, speed, true);
	Ranger::motor_r.MoveTo(-position, speed, true);
}

void Ranger::ColorLoop()
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

void Ranger::StartRainbow()
{
	// on-board LED ring, at PORT0 (onboard)
	Ranger::led.setpin(44);
	Timer::RegisterCallback(Ranger::ColorLoop);
}

void Ranger::StopRainbow()
{
	Timer::UnregisterCallback(Ranger::ColorLoop);
}
