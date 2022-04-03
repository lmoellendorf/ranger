#include <MeAuriga.h>
#include <LmLedRing.h>

void setup()
{
}

void loop()
{
	LedRing::startRainbow();
	delay(2000);
	LedRing::stopRainbow();
	delay(1000);
}
