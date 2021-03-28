#ifndef WALKERLEGS_H
#define WALKERLEGS_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define MAX_SERVO_COUNT 6
#include <Servo.h>


class WalkerLegs
{
    public:
    //конструктор
    WalkerLegs();
    WalkerLegs(int a0, int a1, int a2, int a3, int a4);
    //деструктор
    ~WalkerLegs();

    void forwardSlow(int steps = 1) ;
    void backwardSlow(int steps = 1) ;
    void stopSlow();
    void turnLeft(int angTurn = 36);
    void turnRight(int angTurn = 36);
    void courseDevLeft(int angTurn = 36);
    void courseDevRight(int angTurn = 36);

    private:
    //члены класса
    int servos;

    int angleHor;
    int devAngHor;
    int angMinHor;
    int angMaxHor;

~WalkerLegs();

void begin(int first)

    int angleVer;
    int devAngVer;
    int angMinVer;
    int angMaxVer;

    const int servoCenterConst[6] = {87, 89, 86, 82};
    int servoAngle[6];
    Servo servoLegs[6];
    int rate = 5;
    int delayTime = 100;
    bool debug = true;
    char directionFlag = 's';

    //методы класса
    void begin(int pin = 7);
    void debugPhase(bool debugPhase);
    void sweepVer(char dirSweep);
    void balanceVer();
    void sweepHor(char dirSweep);
    void balanceHor();
};
#endif