/**
 * In this example the "Average" value of the Mindsensors Line Leader is used
 * to calculate a correction value for motor speeds to keep the robot on the
 * line.
 *
 * Edge cases are Average values of
 *
 * 10 -> Line Leader is at RIGHT edge of the line
 * 80 -> Line Leader is at LEFT edge of the line
 *
 * The ideal Average value is:
 *
 * 45 -> Line Leader is in the MIDDLE of the line
 *
 * If average is 80 the robot must turn right. To do so it must
 *
 * -> INCREASE the speed of the LEFT motor and/or
 * -> DECREASE the speed of the RIGHT motor.
 *
 * If average is 10 the robot must turn left. To do so it must

 * -> DECREASE the speed of the LEFT motor and/or
 * -> INCREASE the speed of the RIGHT motor.
 *
 * Calculate a deviation of the ideal value of 45 using the Average (avg):
 *
 * deviation = 45 - avg
 *
 * For 80 it is -> 45 - 80 = -35
 * For 10 it is -> 45 - 10 =  35
 * For 45 it is -> 45 - 45 =   0
 *
 * Add these results to the right motor speed, and substract it from the
 * left motor speed and you will get the desired results.
 */
#include <MeAuriga.h>
#include <LmMsLineLeaderV2.h>
#include <LmEncoderOnBoardMotor.h>

EncoderOnBoardMotor motor_l = EncoderOnBoardMotor(SLOT2);
EncoderOnBoardMotor motor_r = EncoderOnBoardMotor(SLOT1);
MsLineLeaderV2 ll = MsLineLeaderV2();

/* "average" value returned by the sensor */
int avg;
/* last valid "average" value */
int last = 45;
/* normal forward speed */
float normspeed = 50;

void setup() {
}

void loop() {
  float deviation;

  avg = ll.getAverage();

  if (avg != 0) {
    /* if avg is valid, safe it for bad times */
    last = avg;
  } else {
    /**
     * if avg is 0 we lost the line so best option is to keep on going with the
     * last valid value we got
     */
    avg = last;
  }

  /* See top comment for details */
  deviation = 45 - avg;
  /**
   * scale deviaton according to normal speed so it will at most
   *
   * - decrease to 0
   * - increase to double normspeed
   */
  deviation = (deviation / 35.) * normspeed;
  /**
   * This works only if the line leader is built in in forward direction.
   * In forward direction the socket points to the rear of the robot.
   *
   * If the sensor is built in reverse direction, substract deviation from the
   * speed of the right motor and add it to the speed of the left instead.
   */
  motor_r.forward(-(normspeed + deviation));
  motor_l.forward(normspeed - deviation);
}
