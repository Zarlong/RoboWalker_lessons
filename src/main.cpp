#include <Arduino.h>
#include <Servo.h>
#include <Blinker.h>

Blinker LedA;

void setup()
{
    LedA.begin();
}

void loop()
{
    LedA.setTime(millis());
}
