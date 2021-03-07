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
    ~Blinker();
    void setTime(unsigned long tSys);
    void begin(int ledPin = 13);

private:
    int ledPin;
    int ledBlink;
    unsigned long tSys;
    unsigned long tPre;
    bool ledFlag;
    void ledBlinker(unsigned long tSys);
};
#endif