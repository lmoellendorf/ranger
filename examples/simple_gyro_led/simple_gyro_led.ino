#include "MeAuriga.h"
/* needed for I2C communication with gyro sensor */
#include <Wire.h>

/*
 * 0 -> RJ25 port not relevant for on board I2C
 * 0x69 -> I2C device address
 */
MeGyro gyro = MeGyro(0, 0x69);
/*
 * 0 -> RJ25 port not relevant for on board I2C
 * 12 -> number of LEDs
 */
MeRGBLed led_ring = MeRGBLed(0, 12);
/* store gyro sensor values */
double x, y, z;
/* store LED color intensity values */
int r, g, b;

void setup() {
  /* setup and start I2C communication */
  gyro.begin();
  /* set Arduino pin where LED ring is connected to */
  led_ring.setpin(44);
}

void loop() {
  /* read new set of values from sensor */
  gyro.update();

  /* get x axis value : -90 to 90 degree */
  x = gyro.getAngleX();
  /* get y axis value : -90 to 90 degree */
  y = gyro.getAngleY();
  /* get z axis value : -180 to 180 degree */
  z = gyro.getAngleZ();

  /* convert x value to R value: 0 to 255 */
  r = ((x + 90) / 180) * 255;
  /* convert y value to G value: 0 to 255 */
  g = ((y + 90) / 180) * 255;
  /* convert z value to B value: 0 to 255 */
  b = ((z + 180) / 360) * 255;

  /* set RGB color values */
  led_ring.setColor(0, r, g, b);
  /* apply RGB color values */
  led_ring.show();
}
