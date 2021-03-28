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

void WalkerLegs::setDelays(int r, int dT)
{
    rate = r;
    delayTime = dT;
}

void WalkerLegs::sweepVer(char dirSweep) {
    if (dirSweep == 'l') {
    for (angleVer; angleVer < angMaxVer; ++angleVer) {
    for (int j = 1; j < servos; j += 2) {
        ++servoAngle[j];
        servoLegs[j].write(servoAngle[j]);
        delay(rate);
    }
    }
    }
if (dirSweep == 'r') {
    for (angleVer; angleVer > angMinVer; --angleVer) {
    for (int j = 1; j < servos; j += 2) {
        --servoAngle[j];
        servoLegs[j].write(servoAngle[j]);
        delay(rate);
    }
    }
}
DebugPhase(debug);
}

void WalkerLegs::BalanceVer() {
if (angleVer > 90) {
    for (angleVer; angleVer >= 90; --angleVer) {
    for (int j = 1; j < servos; j += 2) {
        --servoAngle[j];
        servoLegs[j].write(servoAngle[j]);
        delay(rate);
    }
    }
}

else if (angleVer < 90) {
    for (angleVer; angleVer <= 90; ++angleVer) {
    for (int j = 1; j < servos; j += 2) {
        ++servoAngle[j];
        servoLegs[j].write(servoAngle[j]);
        delay(rate);
    }
    }
}
DebugPhase(debug);
}

void WalkerLegs::sweepHor(char dirSweep) {
if (dirSweep == 'l') {
    for (angleHor; angleHor < angMaxHor; ++angleHor) {
    for (int j = 0; j < servos; j += 2) {
        if (j != 2) {
        ++servoAngle[j];
        }
        else if (servoAngle[j] <= servoCenterConst[j] + devAngHor) {
        servoAngle[j] += 3;
        }
        servoLegs[j].write(servoAngle[j]);
        delay(rate);
    }
    }
}
if (dirSweep == 'r') {
    for (angleHor; angleHor > angMinHor; --angleHor) {
    for (int j = 0; j < servos; j += 2) {
        if (j != 0) {
        --servoAngle[j];
        }
        else if (servoAngle[j] >= servoCenterConst[j] - devAngHor) {
        servoAngle[j] -= 3;
        }
        servoLegs[j].write(servoAngle[j]);
        delay(rate);
    }
    }
}
DebugPhase(debug);
}
void WalkerLegs::BalanceHor() {
if (angleHor > 90) {
    for (angleHor; angleHor >= 90; --angleHor) {
    for (int j = 0; j < servos; j += 2) {
        --servoAngle[j];
        servoLegs[j].write(servoAngle[j]);
        delay(rate);
    }
    }
    }
    else if (angleHor < 90) {
    for (angleHor; angleHor <= 90; ++angleHor) {
    for (int j = 0; j < servos; j += 2) {
        ++servoAngle[j];
        servoLegs[j].write(servoAngle[j]);
        delay(rate);
    }
    }
}
DebugPhase(debug);
}
void forwardSlow(int steps = 1) {
directionFlag = 'f';
for (int i = 0; i < steps; ++i) {
    SweepHor('l');
    SweepVer('l');
    BalanceHor();
    SweepHor('r');
    SweepVer('r');
    BalanceHor();
}
}
void backwardSlow(int steps = 1) {
directionFlag = 'b';
for (int i = 0; i < steps; ++i) {
    SweepHor('r');
    SweepVer('l');
    BalanceHor();
    SweepHor('l');
    SweepVer('r');
    BalanceHor();
}
}
void stopSlow() {
  if (directionFlag == 'f') {
    SweepHor('l');
    BalanceVer();
    BalanceHor();
  }
  if (directionFlag == 'b') {
    SweepHor('r');
    BalanceVer();
    BalanceHor();
  }
}
void TurnLeft(int angTurn = 36) {

  //первая фаза
  sweepHor('l');
  for (servoAngle[1]; servoAngle[1] <= servoCenterConst[1] + angTurn; ++servoAngle[1]) {
    servoLegs[1].write(servoAngle[1]);
    delay(rate);
  }
  balanceHor();

  //вторая фаза
  sweepHor('r');
  for (servoAngle[3]; servoAngle[3] <= servoCenterConst[3] + angTurn; ++servoAngle[3]) {

    servoAngle[1] -= 1;

    servoLegs[1].write(servoAngle[1]);
    servoLegs[3].write(servoAngle[3]);
    delay(rate);
  }
  balanceHor();

  //третья фаза
  sweepHor('l');
  for (servoAngle[1]; servoAngle[1] <= servoCenterConst[1] + angTurn; ++servoAngle[1]) {

    servoAngle[3] -= 1;
    servoLegs[1].write(servoAngle[1]);
    servoLegs[3].write(servoAngle[3]);
    delay(rate);
  }
  BalanceHor();

  //четвертая  фаза
  sweepHor('r');
  for (servoAngle[1]; servoAngle[1] >= servoCenterConst[1]; --servoAngle[1]) {
    servoLegs[1].write(servoAngle[1]);
    delay(rate);
  }
  BalanceHor();
}
void TurnRight(int angTurn = 36) {

  //первая фаза
  SweepHor('r');
  for (servoAngle[3]; servoAngle[3] >= servoCenterConst[3] - angTurn; --servoAngle[3]) {
    servoLegs[3].write(servoAngle[3]);
    delay(rate);
  }
  BalanceHor();

  //вторая фаза
  SweepHor('l');
  for (servoAngle[1]; servoAngle[1] >= servoCenterConst[1] - angTurn; --servoAngle[1]) {

    servoAngle[3] += 1;

    servoLegs[1].write(servoAngle[1]);
    servoLegs[3].write(servoAngle[3]);
    delay(rate);
  }
  BalanceHor();

  //третья фаза
  SweepHor('r');
for (servoAngle[3]; servoAngle[3] >= servoCenterConst[3] - angTurn; --servoAngle[3]) {

    servoAngle[1] += 1;
    servoLegs[1].write(servoAngle[1]);
    servoLegs[3].write(servoAngle[3]);
    delay(rate);
}
BalanceHor();

  //четвертая  фаза
  SweepHor('l');
  for (servoAngle[3]; servoAngle[3] <= servoCenterConst[3]; ++servoAngle[3]) {
    servoLegs[3].write(servoAngle[3]);
    delay(rate);
  }
  BalanceHor();
}


