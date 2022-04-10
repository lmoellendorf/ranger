/**
 * Follow an IR beacon, e.g. RCJ IR electronic ball unsing an HiTechnic IR
 * Seeker V2 for LEGO Mindstorms.
 */
#include<MeAuriga.h>
#include <LmMeHtIrSeekerV2.h>
#include <LmEncoderOnBoardMotor.h>

MeHtIrSeekerV2 seeker;
EncoderOnBoardMotor motor_l(SLOT2);
EncoderOnBoardMotor motor_r(SLOT1);

void setup()
{
	seeker = MeHtIrSeekerV2(PORT_6, MeHtIrSeekerV2::AC);
}

void loop()
{
	int ret;

	ret = seeker.getDirection(true);

	if (ret == 0)
		return;

	motor_l.forward(100 + (ret - 5) * 20);
	motor_r.forward(-100 - (ret - 5) * -20);
}
