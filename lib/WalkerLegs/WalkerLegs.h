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
    WalkerLegs(int a0, int a1, int a2, int a3);
    //деструктор
    ~WalkerLegs();


    void begin(int pin = 7);
    void forwardSlow(int steps = 1); 
    void backwardSlow(int steps = 1); 
    void stopSlow();
    void turnLeft(int angTurn = 36);
    void turnRight(int angTurn = 36);
    void courseDevLeft(int angTurn = 36);
    void courseDevRight(int angTurn = 36);
    void setDelays(int r = 10, int dT = 100);
    
     private:
    //члены класса
    int servos;

    int angleHor;
    int devAngHor;
    int angMinHor;
    int angMaxHor;

    int angleVer;
    int devAngVer;
    int angMinVer;
    int angMaxVer;

    int servoCenterConst[6];
    int servoAngle[6];
    Servo servoLegs[6];
    int first;
    int rate;
    int delayTime;
    bool debug = true;
    char directionFlag = 's';

    //методы класса
   

    void setDeviation(int dAHor = 50, int dAVer = 20);
    void debugPhase(bool debugPhase);
    void sweepVer(char dirSweep);
    void balanceVer();
    void sweepHor(char dirSweep);
    void balanceHor();
};

#endif