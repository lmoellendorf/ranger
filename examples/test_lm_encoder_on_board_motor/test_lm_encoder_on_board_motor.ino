#include <MeAuriga.h>
#include <LmEncoderOnBoardMotor.h>
#include <LmLedRing.h>

EncoderOnBoardMotor motor_l(SLOT2);
EncoderOnBoardMotor motor_r(SLOT1);

void setup()
{
	Serial.begin(115200);
	motor_r.ResetTachoCount();
	motor_l.ResetTachoCount();
	Serial.print(" left tacho count=");
	Serial.println(motor_l.GetTachoCount());
	Serial.print("right tacho count=");
	Serial.println(motor_r.GetTachoCount());
}

void HeartBeat(void)
{
	buzzerOn();
	delay(333);
	buzzerOff();
	delay(666);
}

static void printTachoCount(void)
{
	int t_l, t_r;

	t_l = motor_l.GetTachoCount();
	t_r = motor_r.GetTachoCount();
	Serial.print(" left tacho count=");
	Serial.println(t_l);
	Serial.print("right tacho count=");
	Serial.println(t_r);
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
	printTachoCount();
	//Rotate and block until position is reached
	motor_l.Rotate(-turn90, 200, false, true);
	motor_r.Rotate(-turn90, 200, true, true);
	printTachoCount();
	//Move forward and block until position is reached
	motor_l.Rotate(path2, 200, false, true);
	motor_r.Rotate(-path2, 200, true, true);
	printTachoCount();
	//Rotate and block until position is reached
	motor_l.Rotate(-turn90, 200, false, true);
	motor_r.Rotate(-turn90, 200, true, true);
	printTachoCount();
	//Move forward and block until position is reached
	motor_l.Rotate(path3, 200, false, true);
	motor_r.Rotate(-path3, 200, true, true);
	printTachoCount();
	//Rotate and block until position is reached
	motor_l.Rotate(turn90, 200, false, true);
	motor_r.Rotate(turn90, 200, true, true);
	printTachoCount();
	//Move forward and block until position is reached
	motor_l.Rotate(path4, 200, false, true);
	motor_r.Rotate(-path4, 200, true, true);
	printTachoCount();

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

	printTachoCount();
	motor_r.ResetTachoCount();
	motor_l.ResetTachoCount();
	printTachoCount();

	while (1) {
		motor_l.Stop();
		motor_r.Stop();
	}
}
