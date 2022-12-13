#include "MeAuriga.h"

MeRGBLed led_ring = MeRGBLed(0, 12);

void setup()
{
	led_ring.setpin(44);
}

uint8_t dim(double n_led, double led)
{
	return 255. * (-n_led * pow(led, 2) + pow(n_led,
			2) * led) / (-n_led * pow(n_led / 2., 2) + pow(n_led, 2) * n_led / 2.);
}

void loop()
{
	int n_led = 12;

	for (int i = 0; i < 12; i++) {
		led_ring.setColor(0, 0, 0, 0) ;

		for (int j = 0; j < n_led; j++)
			led_ring.setColor(((i + j) % 12) + 1, dim(n_led, j), dim(n_led,
					  (j + n_led / 2) % n_led), dim(n_led, (j + n_led / 4) % n_led)) ;

		led_ring.show();
		delay(100);
	}
}
