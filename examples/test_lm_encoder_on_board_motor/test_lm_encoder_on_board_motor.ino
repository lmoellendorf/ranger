#include <MeAuriga.h>
#include <LmEncoderOnBoardMotor.h>

EncoderOnBoardMotor motor_l(SLOT2);
EncoderOnBoardMotor motor_r(SLOT1);

void setup()
{
}

void HeartBeat(void)
{
	pinMode(45, OUTPUT);
	digitalWrite(45, HIGH);
	delay(333);
	pinMode(45, OUTPUT);
	digitalWrite(45, LOW);
	delay(666);
}

void loop()
{
	HeartBeat();

	//Move forward and block until position is reached
	motor_l.RotateTo(360, 200);
	motor_r.RotateTo(-360, 200, true);
	//Rotate and block until position is reached
	motor_l.RotateTo(360, 200, false);
	motor_r.RotateTo(360, 200, true);

	HeartBeat();

	//Move forward and block until position is reached synchronized
	motor_l.RotateTo(360, 200, false, true);
	motor_r.RotateTo(-360, 200, true, true);
	//Rotate and block until position is reached synchronized
	motor_l.RotateTo(360, 200, false, true);
	motor_r.RotateTo(360, 200, true, true);

	while (1) {
		HeartBeat();
		motor_l.Stop();
		motor_r.Stop();
	}
}
