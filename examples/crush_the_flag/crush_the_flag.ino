#include <MeAuriga.h>
#include <LmEncoderOnBoardMotor.h>
#include <LmLedRing.h>

EncoderOnBoardMotor motor_l(SLOT2);
EncoderOnBoardMotor motor_r(SLOT1);

MeUltrasonicSensor us_l(PORT_6);
MeUltrasonicSensor us_r(PORT_7);
MeUltrasonicSensor us_f(PORT_8);

void setup()
{
}

const int path1 = 4000;
const int turn90 = 410;
const int path2 = 750;
const int path3 = 2600;
const int path4 = 780;

const int ENCODER = 0;
const int ULTRA_SONIC = 1;
const int LINE_LEADER = 2;
const int BUTTON_PUSH = 2;
int state = ENCODER;

void loop()
{
  float dist_l, dist_r, dist_f;
  int speed_l, speed_r;

  dist_l = us_l.distanceCm();
  dist_r = us_r.distanceCm();
  dist_f = us_f.distanceCm();
  
  switch(state){
    case ENCODER:
	    LedRing::StopRainbow();
	    //Move forward and block until position is reached
	    motor_l.RotateTo(path1, 200, false, true);
	    motor_r.RotateTo(-path1, 200, true, true);
      state = ULTRA_SONIC;
    break;

    case ULTRA_SONIC:
      if(dist_f < 15) {
        // steht vor Wand
        if(dist_l < dist_r) {
          // drehe auf der Stelle nach rechts
          speed_l = 200;
          speed_r = 200;
        } else {
          // drehe auf der Stelle nach links
          speed_l = -200;
          speed_r = -200;
        }
      }
      else {
      // faehrt im Gang
      if(dist_l < dist_r) {
          // drehe nach rechts
          speed_l = 200 + (dist_r - dist_l);
          speed_r = -200 + (dist_r - dist_l);
      } else {
          // drehe nach links
          speed_l = 200 - (dist_l - dist_r);
          speed_r = -200 - (dist_l - dist_r);
      }
      {

      motor_l.Forward(speed_l);      
      motor_r.Forward(speed_r);
            
      if(/* Lineleader erkennt weiss */0){
        state = 2;
      }
    break;

    case LINE_LEADER:
    // Linienfolger
    break;

    case BUTTON_PUSH:
    // Button press
    break;
  }
	LedRing::StartRainbow();

  
}
