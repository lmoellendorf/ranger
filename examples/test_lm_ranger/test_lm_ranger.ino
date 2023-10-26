#include <MeAuriga.h>
#include <LmRanger.h>
#include <LmLedRing.h>

Ranger ranger = Ranger(SLOT_L, SLOT_R);

void setup() {
  LedRing::startRainbow();
}

void loop() {
  ranger.moveTo(6000, 200);
}
