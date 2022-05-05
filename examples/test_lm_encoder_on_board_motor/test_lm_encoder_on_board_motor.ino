#include <MeAuriga.h>
#include <LmEncoderOnBoardMotor.h>
#include <LmLedRing.h>

EncoderOnBoardMotor motor_l(SLOT2);
EncoderOnBoardMotor motor_r(SLOT1);

void setup()
{
	Serial.begin(115200);
	motor_r.resetTachoCount();
	motor_l.resetTachoCount();
	Serial.print(" left tacho count=");
	Serial.println(motor_l.getTachoCount());
	Serial.print("right tacho count=");
	Serial.println(motor_r.getTachoCount());
}

void heartBeat(void)
{
	buzzerOn();
	delay(333);
	buzzerOff();
	delay(666);
}

static void printTachoCount(void)
{
	int t_l, t_r;

	t_l = motor_l.getTachoCount();
	t_r = motor_r.getTachoCount();
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

	LedRing::stopRainbow();
	//Move forward and block until position is reached
	motor_l.rotate(path1, 200, false, true);
	motor_r.rotate(-path1, 200, true, true);
	printTachoCount();
	//Rotate and block until position is reached
	motor_l.rotate(-turn90, 200, false, true);
	motor_r.rotate(-turn90, 200, true, true);
	printTachoCount();
	//Move forward and block until position is reached
	motor_l.rotate(path2, 200, false, true);
	motor_r.rotate(-path2, 200, true, true);
	printTachoCount();
	//Rotate and block until position is reached
	motor_l.rotate(-turn90, 200, false, true);
	motor_r.rotate(-turn90, 200, true, true);
	printTachoCount();
	//Move forward and block until position is reached
	motor_l.rotate(path3, 200, false, true);
	motor_r.rotate(-path3, 200, true, true);
	printTachoCount();
	//Rotate and block until position is reached
	motor_l.rotate(turn90, 200, false, true);
	motor_r.rotate(turn90, 200, true, true);
	printTachoCount();
	//Move forward and block until position is reached
	motor_l.rotate(path4, 200, false, true);
	motor_r.rotate(-path4, 200, true, true);
	printTachoCount();

	heartBeat();

	//Do not block
	motor_l.rotate(360, 200);
	motor_r.rotate(-360, 200);
	delay(333);
	motor_l.stop();
	motor_r.stop();
	heartBeat();
	delay(333);

	motor_l.forward(100);
	motor_r.forward(-100);
	delay(3000);
	LedRing::startRainbow();

	printTachoCount();
	motor_r.resetTachoCount();
	motor_l.resetTachoCount();
	printTachoCount();

	while (1) {
		motor_l.stop();
		motor_r.stop();
	}
}
