#include "MeAuriga.h"

MeRGBLed led_ring = MeRGBLed(0, 12);
int i = 0;

void setup()
{
	led_ring.setpin(44);
}

void loop()
{
	int led;
	/* 0 <= led <= 11 */
	led = (i % 12);
	/* 1 <= led <= 12 */
	led++;
	led_ring.setColor(0, 0, 0, 0);
	led_ring.setColor(led, 255, 0, 0);
	led_ring.show();
	delay(100);
	i++;
}
