#include <MeAuriga.h>
#include "MeRGBLineFollower.h"
#include "LmEncoderOnBoardMotor.h"

EncoderOnBoardMotor motor_l = EncoderOnBoardMotor(SLOT2);
EncoderOnBoardMotor motor_r = EncoderOnBoardMotor(SLOT1);
MeRGBLineFollower linefollower = MeRGBLineFollower(PORT_6, ADDRESS2);

int16_t turnoffset = 0;
int16_t set_speed = 50;
/*
 * Orientation of the left motor relative to the robot
 *
 *  1: drive forward
 * -1: drive backward
 */
int orientation = -1;

void setup() {
  linefollower.begin();
  linefollower.setKp(0.3);
}

void loop() {
  linefollower.loop();

  turnoffset = linefollower.getPositionOffset();

  motor_l.forward(orientation * (set_speed - turnoffset));
  motor_r.forward(orientation * -(set_speed + turnoffset));
}
