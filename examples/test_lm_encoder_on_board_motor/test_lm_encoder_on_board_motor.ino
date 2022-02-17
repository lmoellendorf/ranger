#include <MeAuriga.h>
#include <LmEncoderOnBoardMotor.h>
#include <LmLedRing.h>

EncoderOnBoardMotor motor_l(SLOT2);
EncoderOnBoardMotor motor_r(SLOT1);

void setup()
{
}

void HeartBeat(void)
{
	buzzerOn();
	delay(333);
	buzzerOff();
	delay(666);
}

void loop()
{
	int path1 = 4000;
	int turn90 = 410;
	int path2 = 750;
	int path3 = 2600;
	int path4 = 780;

	LedRing::StopRainbow();
	//Move forward and block until position is reached
	motor_l.Rotate(path1, 200, false, true);
	motor_r.Rotate(-path1, 200, true, true);
	//Rotate and block until position is reached
	motor_l.Rotate(-turn90, 200, false, true);
	motor_r.Rotate(-turn90, 200, true, true);
	//Move forward and block until position is reached
	motor_l.Rotate(path2, 200, false, true);
	motor_r.Rotate(-path2, 200, true, true);
	//Rotate and block until position is reached
	motor_l.Rotate(-turn90, 200, false, true);
	motor_r.Rotate(-turn90, 200, true, true);
	//Move forward and block until position is reached
	motor_l.Rotate(path3, 200, false, true);
	motor_r.Rotate(-path3, 200, true, true);
	//Rotate and block until position is reached
	motor_l.Rotate(turn90, 200, false, true);
	motor_r.Rotate(turn90, 200, true, true);
	//Move forward and block until position is reached
	motor_l.Rotate(path4, 200, false, true);
	motor_r.Rotate(-path4, 200, true, true);

	HeartBeat();

	//Do not block
	motor_l.Rotate(360, 200);
	motor_r.Rotate(-360, 200);
	delay(333);
	motor_l.Stop();
	motor_r.Stop();
	HeartBeat();
	delay(333);

	motor_l.Forward(100);
	motor_r.Forward(-100);
	delay(3000);
	LedRing::StartRainbow();

	while (1) {
		motor_l.Stop();
		motor_r.Stop();
	}
}
