#ifndef BLINKER_H
#define BLINKER_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class Blinker
{

public:
    Blinker();
    Blinker(int pin, int hz);
    Blinker(int pin, int tl, int td);
    ~Blinker();
    void setTime(unsigned long tSys);
    void begin(int ledPin);

private:
    int ledPin;
    int ledBlink;
    int ledBlack;
    unsigned long tSys;
    unsigned long tPre;
    bool ledFlag;
    
    void ledBlinker(unsigned long tSys);
};
#endif