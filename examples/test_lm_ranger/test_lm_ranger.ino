#include <MeAuriga.h>
#include <LmRanger.h>

Ranger ranger(SLOT_L, SLOT_R);

void setup()
{
}

void loop()
{
	pinMode(45, OUTPUT);
	digitalWrite(45, HIGH);
	delay(250);
	pinMode(45, OUTPUT);
	digitalWrite(45, LOW);
	delay(750);

	ranger.MoveTo(6000, 200);
	ranger.StartRainbow();
}
