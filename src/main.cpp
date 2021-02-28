#include <Arduino.h>
#include <Servo.h>
#include <Blinker.h>

Blinker LedA;
Blinker LedB(12, 2);

void setup()
{
    LedA.begin();
    LedB.begin();
}

void loop()
{
    LedA.setTime(millis());
    LedB.setTime(millis());
}
