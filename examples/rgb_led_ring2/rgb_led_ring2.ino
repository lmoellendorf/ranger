#include "MeAuriga.h"

MeRGBLed led_ring = MeRGBLed(0, 12);

void setup()
{
	led_ring.setpin(44);
}

void loop()
{
	for (int i = 0; i < 12; i++) {
		led_ring.setColor(0, 0, 0, 0);

		for (int j = 0; j < 5; j++)
			led_ring.setColor(((i + j) % 12) + 1, 255, 0, 0) ;

		led_ring.show();
		delay(100);
	}
}
