#include <MeAuriga.h>
#include <LmLedRing.h>
#include <LmNxtTouch.h>

NxtTouch touch = NxtTouch(PORT6);

void setup()
{
}

void loop()
{
	bool down = touch.isDown();

	if (down)
		LedRing::startRainbow();
	else
		LedRing::stopRainbow();
}
