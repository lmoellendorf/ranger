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

	//Do not block
	motor_l.RotateTo(360, 200);
	motor_r.RotateTo(-360, 200);
	delay(333);
	motor_l.Stop();
	motor_r.Stop();
	HeartBeat();
	delay(333);

	motor_l.Forward(100);
	motor_r.Forward(-100);
	delay(3000);

	while (1) {
		HeartBeat();
		motor_l.Stop();
		motor_r.Stop();
	}
}
