#include <MeAuriga.h>
#include <LmLedRing.h>

MeSoundSensor mySound = MeSoundSensor(0);

void setup() {
  Serial.begin(9600);
  mySound.setpin(A1);
}

void loop() {
  int strength;
  strength = mySound.strength();
  Serial.print("value=");
  Serial.println(strength);

  if (strength > 200)
    LedRing::startRainbow();

  else
    LedRing::stopRainbow();

  delay(100);
}
