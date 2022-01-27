#include <MeAuriga.h>
#include <LmEncoderOnBoardMotor.h>

EncoderOnBoardMotor motor_l(SLOT2);
EncoderOnBoardMotor motor_r(SLOT1);

void setup() {
}

void loop() {
  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);
  delay(333);
  pinMode(45, OUTPUT);
  digitalWrite(45, LOW);
  delay(666);

  //Move forward and block until position is reached
  motor_l.RotateTo(360, 200);
  motor_r.RotateTo(-360, 200, true);
  //Rotate and block until position is reached
  motor_l.RotateTo(360, 200, false);
  motor_r.RotateTo(360, 200, true);
}
