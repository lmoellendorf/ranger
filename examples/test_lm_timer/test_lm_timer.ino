#include <MeAuriga.h>
#include <LmLedRing.h>

void setup()
{
}

void loop()
{
	LedRing::StartRainbow();
	delay(2000);
	LedRing::StopRainbow();
	delay(1000);
}
