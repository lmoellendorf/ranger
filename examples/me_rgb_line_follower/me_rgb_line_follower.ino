#include <MeAuriga.h>
#include "MeRGBLineFollower.h"
#include "LmEncoderOnBoardMotor.h"

EncoderOnBoardMotor motor_l = EncoderOnBoardMotor(SLOT2);
EncoderOnBoardMotor motor_r = EncoderOnBoardMotor(SLOT1);
MeRGBLineFollower linefollower = MeRGBLineFollower(PORT_6, ADDRESS2);

int16_t turnoffset = 0;
int16_t set_speed = 50;

void setup() {
  linefollower.begin();
  linefollower.setKp(0.3);
}

void loop() {
  linefollower.loop();

  turnoffset = linefollower.getPositionOffset();

  motor_l.forward(set_speed + turnoffset);
  motor_r.forward(-(set_speed - turnoffset));
}
