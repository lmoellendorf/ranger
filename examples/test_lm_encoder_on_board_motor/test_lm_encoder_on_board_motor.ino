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

	LedRing::StopRainbow();
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
	LedRing::StartRainbow();

	while (1) {
		motor_l.Stop();
		motor_r.Stop();
	}
}
