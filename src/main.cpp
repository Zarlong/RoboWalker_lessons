#include <Arduino.h>
#include <Servo.h>
#include <Blinker.h>

Blinker LedA;
Blinker LedB(12, 2);
Blinker LedC(11, 200, 500);

void setup()
{
    
}

void loop()
{
    LedA.setTime(millis());
    LedB.setTime(millis());
    LedC.setTime(millis());
}
