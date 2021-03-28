#include <Arduino.h>
#include "WalkerLegs.h"

WalkerLegs hutOnClickenLegs(87, 89, 86, 82);

void setup() {
  hutOnClickenLegs.begin();
  hutOnClickenLegs.setDelays(10, 1500);
}

void loop() {
  
  // put your main code here, to run repeatedly:
}