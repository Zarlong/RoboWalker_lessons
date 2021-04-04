#include "WalkerLegs.h"

WalkerLegs::WalkerLegs()
{
    servos = 4;
    servoCenterConst[0] = 90;
    servoCenterConst[1] = 90;
    servoCenterConst[2] = 90;
    servoCenterConst[3] = 90;
}

WalkerLegs::WalkerLegs(int a0, int a1, int a2, int a3)
{
    servos = 4;
    servoCenterConst[0] = a0;
    servoCenterConst[1] = a1;
    servoCenterConst[2] = a2;
    servoCenterConst[3] = a3;
}

WalkerLegs::~WalkerLegs(){}

void WalkerLegs::begin(int pin)
{
  for (int i = 0; i < servos; ++i) {
    servoAngle[i] = servoCenterConst[i];         //заполняем новый, изменяемый массив для хранения текущего положения сервоприводов
    servoLegs[i].attach(i + pin);                  //инициализируем порты с сервоприводами
    servoLegs[i].write(servoCenterConst[i]);      //выставляем начальное положение сервопривода
    delay(500);
  }
setDeviation();
setDelays();
}

void WalkerLegs::setDeviation(int dAHor , int dAVer ){

angleHor = 90;
devAngHor = dAHor;
angMinHor = angleHor - devAngHor;
angMaxHor = angleHor + devAngHor;

angleVer = 90;
devAngVer = dAVer;
angMinVer = angleVer - devAngVer;
angMaxVer = angleVer + devAngVer;
}

void WalkerLegs::setDelays(int r, int dT){
    rate = r;
    delayTime = dT;
}

void WalkerLegs::debugPhase(bool debugPhase) {
  if (debugPhase == true) 
  {
    delay(delayTime);
  }

}
//функция для шага вперёд
void WalkerLegs::sweepVer(char dirSweep) 
{
  if (dirSweep == 'l') 
  {
    for (angleVer; angleVer < angMaxVer; ++angleVer) 
    {
      for (int j = 1; j < servos; j += 2) 
      {
        ++servoAngle[j];
        servoLegs[j].write(servoAngle[j]);
        delay(rate);
      }
    }
  }
  if (dirSweep == 'r') 
  {
    for (angleVer; angleVer > angMinVer; --angleVer)
     {
      for (int j = 1; j < servos; j += 2) 
      {
        --servoAngle[j];
        servoLegs[j].write(servoAngle[j]);
        delay(rate);
      }
    }
  }
  debugPhase(debug);
}

//функция для возвращения в исходное положение
void WalkerLegs::balanceVer() 
{
  if (angleVer > 90) 
  {
    for (angleVer; angleVer >= 90; --angleVer) 
    {
      for (int j = 1; j < servos; j += 2) 
      {
        --servoAngle[j];
        servoLegs[j].write(servoAngle[j]);
        delay(rate);
      }
    }
  }

  else if (angleVer < 90) 
  {
    for (angleVer; angleVer <= 90; ++angleVer) 
    {
      for (int j = 1; j < servos; j += 2) 
      {
        ++servoAngle[j];
        servoLegs[j].write(servoAngle[j]);
        delay(rate);
      }
    }
  }
  debugPhase(debug);
}

//функция для отклонения вбок
void WalkerLegs::sweepHor(char dirSweep)
 {
  if (dirSweep == 'l') {
    for (angleHor; angleHor < angMaxHor; ++angleHor)
     {
      for (int j = 0; j < servos; j += 2) {
        if (j != 2)
         {
          ++servoAngle[j];
        }
        else if (servoAngle[j] <= servoCenterConst[j] + devAngHor)
         {
          servoAngle[j] += 3;
        }
        servoLegs[j].write(servoAngle[j]);
        delay(rate);
      }
    }
  }
  if (dirSweep == 'r') 
  {
    for (angleHor; angleHor > angMinHor; --angleHor) 
    {
      for (int j = 0; j < servos; j += 2) 
      {
        if (j != 0) 
        {
          --servoAngle[j];
        }
        else if (servoAngle[j] >= servoCenterConst[j] - devAngHor) 
        {
          servoAngle[j] -= 3;
        }
        servoLegs[j].write(servoAngle[j]);
        delay(rate);
      }
    }
  }
  debugPhase(debug);
}

//функция для возвращения в исходное положение
void WalkerLegs::balanceHor() 
{
  if (angleHor > 90) 
  {
    for (angleHor; angleHor >= 90; --angleHor)
    {
      for (int j = 0; j < servos; j += 2) {
        --servoAngle[j];
        servoLegs[j].write(servoAngle[j]);
        delay(rate);
      }
    }
  }

  else if (angleHor < 90) 
  {
    for (angleHor; angleHor <= 90; ++angleHor) 
    {
      for (int j = 0; j < servos; j += 2) 
      {
        ++servoAngle[j];
        servoLegs[j].write(servoAngle[j]);
        delay(rate);
      }
    }
  }
  debugPhase(debug);
}
void WalkerLegs::forwardSlow(int steps = 1) {
  directionFlag = 'f';
  for (int i = 0; i < steps; ++i) {
    sweepHor('l');
    sweepVer('l');
    balanceHor();
    sweepHor('r');
    sweepVer('r');
    balanceHor();
  }
}

void WalkerLegs::backwardSlow(int steps = 1) {
  directionFlag = 'b';
  for (int i = 0; i < steps; ++i) {
    sweepHor('r');
    sweepVer('l');
    balanceHor();
    sweepHor('l');
    sweepVer('r');
    balanceHor();
  }
}

void WalkerLegs::stopSlow() {
  if (directionFlag == 'f') {
    sweepHor('l');
    balanceVer();
    balanceHor();
  }
  if (directionFlag == 'b') {
    sweepHor('r');
    balanceVer();
    balanceHor();
  }
}
void WalkerLegs::turnLeft(int angTurn = 36) {

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
  balanceHor();

  //четвертая  фаза
  sweepHor('r');
  for (servoAngle[1]; servoAngle[1] >= servoCenterConst[1]; --servoAngle[1]) {
    servoLegs[1].write(servoAngle[1]);
    delay(rate);
  }
  balanceHor();
}


void WalkerLegs::turnRight(int angTurn = 36) {

  //первая фаза
  sweepHor('r');
  for (servoAngle[3]; servoAngle[3] >= servoCenterConst[3] - angTurn; --servoAngle[3]) {
    servoLegs[3].write(servoAngle[3]);
    delay(rate);
  }
  balanceHor();

  //вторая фаза
  sweepHor('l');
  for (servoAngle[1]; servoAngle[1] >= servoCenterConst[1] - angTurn; --servoAngle[1]) {

    servoAngle[3] += 1;

    servoLegs[1].write(servoAngle[1]);
    servoLegs[3].write(servoAngle[3]);
    delay(rate);
  }
  balanceHor();

  //третья фаза
  sweepHor('r');
  for (servoAngle[3]; servoAngle[3] >= servoCenterConst[3] - angTurn; --servoAngle[3]) {

    servoAngle[1] += 1;
    servoLegs[1].write(servoAngle[1]);
    servoLegs[3].write(servoAngle[3]);
    delay(rate);
  }
  balanceHor();

  //четвертая  фаза
  sweepHor('l');
  for (servoAngle[3]; servoAngle[3] <= servoCenterConst[3]; ++servoAngle[3]) {
    servoLegs[3].write(servoAngle[3]);
    delay(rate);
  }
  balanceHor();
}
void WalkerLegs::courseDevLeft(int angTurn = 36) {

  //первая фаза
  sweepHor('l');
  for (servoAngle[1]; servoAngle[1] <= servoCenterConst[1] + angTurn; ++servoAngle[1]) {
    servoLegs[1].write(servoAngle[1]);
    delay(rate);
  }
  balanceHor();


  //четвертая  фаза
  sweepHor('r');
  for (servoAngle[1]; servoAngle[1] >= servoCenterConst[1]; --servoAngle[1]) {
    servoLegs[1].write(servoAngle[1]);
    delay(rate);
  }
  balanceHor();
}


void WalkerLegs::courseDevRight(int angTurn = 36) {

  //первая фаза
  sweepHor('r');
  for (servoAngle[3]; servoAngle[3] >= servoCenterConst[3] - angTurn; --servoAngle[3]) {
    servoLegs[3].write(servoAngle[3]);
    delay(rate);
  }
  balanceHor();

  //четвертая  фаза
  sweepHor('l');
  for (servoAngle[3]; servoAngle[3] <= servoCenterConst[3]; ++servoAngle[3]) {
    servoLegs[3].write(servoAngle[3]);
    delay(rate);
  }
  balanceHor();
}


