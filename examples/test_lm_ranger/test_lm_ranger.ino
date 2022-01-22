#include <MeAuriga.h>
#include <LmRanger.h>

Ranger ranger(SLOT_L, SLOT_R);

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  pinMode(45, OUTPUT);
  digitalWrite(45, HIGH);
  delay(250);
  pinMode(45, OUTPUT);
  digitalWrite(45, LOW);
  delay(750);

  ranger.moveTo(360, 200);
}
