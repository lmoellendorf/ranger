#include <MeAuriga.h>
#include <LmEncoderOnBoardMotor.h>

EncoderOnBoardMotor motor(SLOT2);

void setup() {
}

void loop() {
  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);
  delay(250);
  pinMode(45, OUTPUT);
  digitalWrite(45, LOW);
  delay(750);

  motor.move_to(360, 200);
}
