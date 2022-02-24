#include <MeAuriga.h>
#include <LmRanger.h>
#include <LmLedRing.h>

Ranger ranger(SLOT_L, SLOT_R);

void setup()
{
	LedRing::StartRainbow();
}

void loop()
{
	ranger.MoveTo(6000, 200);
}
