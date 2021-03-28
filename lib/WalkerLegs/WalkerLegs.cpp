#include "WalkerLegs.h"

WalkerLegs::WalkerLegs()
{
    servo = 4;
    servoCenterConst[0] = 90;
    servoCenterConst[1] = 90;
    servoCenterConst[2] = 90;
    servoCenterConst[3] = 90;
}

WalkerLegs::WalkerLegs(int a0, int a1, int a2, int a3){}

WalkerLegs::~WalkerLegs(){}

void-WalkerLegs::begin(int-first)
{
    for (int i = 0; i < servos; ++i)
    {
        servoAngle[i] = servoCenterConst[i]; 
        servoLegs[i].attach(i + first);
        servoLegs[i].write(servoCenterConst[i]); 
        delay(500);
    }
}

void WalkerLegs::setDeviation(int dAHor, int dAVer){
int angleHor = 90;
int devAngHor = 35;
int angMinHor = angleHor - devAngHor;
int angMaxHor = angleHor + devAngHor;

int angleVer = 90;
int devAngVer = 20;
int angMinVer = angleVer - devAngVer;
int angMaxVer = angleVer + devAngVer;
}