/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Simplified Ranger RGB LED Ring controls
 *
 * @details
 */

#include "LmLedRing.h"
#include "LmTimer.h"

// Auriga on-board light ring has 12 LEDs
#define LEDNUM  12

MeRGBLed LedRing::led(0, LEDNUM);
volatile float LedRing::j(0), LedRing::f(0), LedRing::k(0);
volatile int t = 0;

void LedRing::ColorLoop()
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

void LedRing::StartRainbow()
{
	// on-board LED ring, at PORT0 (onboard)
	led.setpin(44);
	Timer::RegisterCallback(ColorLoop);
}

void LedRing::StopRainbow()
{
	Timer::UnregisterCallback(ColorLoop);

	for (int n = 0; n < LEDNUM; n++) {
		led.setColorAt(n, 0, 0, 0);
		led.show();
	}
}
