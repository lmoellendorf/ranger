#include <MeAuriga.h>
#include <Wire.h>

MeEncoderNew motor = MeEncoderNew(0x11, SLOT1);
/**
 * Old encoder has fixed I2C address
 */
// MeEncoderMotor motor = MeEncoderMotor(0x09, SLOT1);

void setup() {
  Serial.begin(9600);
  motor.begin();
}

void loop() {
  motor.runSpeed(100);
  delay(1000);
  motor.runSpeed(0);
  delay(1000);
  motor.reset();
}
