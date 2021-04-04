//подключаем заголовочный файл
#include "WalkerLegs.h"

// Конструктор по умолчанию для первоначальной отстройки
WalkerLegs::WalkerLegs()
{
  servos = 4;
  servoCenterConst[0] = 90;
  servoCenterConst[1] = 90;
  servoCenterConst[2] = 90;
  servoCenterConst[3] = 90;
}

// Описание конструктора с параметрами при известных углах суставов
WalkerLegs::WalkerLegs(int a0, int a1, int a2, int a3)
{
  servos = 4;
  servoCenterConst[0] = a0;
  servoCenterConst[1] = a1;
  servoCenterConst[2] = a2;
  servoCenterConst[3] = a3;
}

//пустой деструктор
WalkerLegs::~WalkerLegs() {}

//метод для инициализации портов с подключенными сервоприводами и установки их уголов
void WalkerLegs::begin(int first)
{
  for (int i = 0; i < servos; ++i)
  {
    servoAngle[i] = servoCenterConst[i];     //заполняем новый изменяемый массив для хранения текущего положения сервоприводов
    servoLegs[i].attach(i + first);          //инициализируем порты с сервоприводами
    servoLegs[i].write(servoCenterConst[i]); //выставляем начальное положение сервопривода
    delay(500);
  }
  setDeviation();
  setDelays();
}

//методы установки отклонений по вертикальным и горизонтальным осям
void WalkerLegs::setDeviation(int dAHor, int dAVer)
{
  angleHor = 90;
  devAngHor = dAHor;
  angMinHor = angleHor - devAngHor;
  angMaxHor = angleHor + devAngHor;

  angleVer = 90;
  devAngVer = dAVer;
  angMinVer = angleVer - devAngVer;
  angMaxVer = angleVer + devAngVer;
}

//установка скорости движений через изменение задержек между 
void WalkerLegs::setDelays(int r, int dT)
{
  rate = r;
  delayTime = dT;
}

//метод для подключения или отключения задержки между фазами перемещения
void WalkerLegs::debugPhase(bool debugPhase)
{
  if (debugPhase == true)
  {
    delay(delayTime);
  }
}

//метод для вращения вертикальных осей сервоприводов
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

//метод для возвращения вертикальных сервоприводов в исходное положение
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
  else if(angleVer < 90)
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

//метод для отклонения горизонтальных осей суставов
void WalkerLegs::sweepHor(char dirSweep)
{
  if (dirSweep == 'l')
  {
    for (angleHor; angleHor < angMaxHor; ++angleHor)
    {
      for (int j = 0; j < servos; j += 2)
      {
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

//методы для возвращения горизонтальных осей в исходное положение
void WalkerLegs::balanceHor()
{
  if (angleHor > 90)
  {
    for (angleHor; angleHor >= 90; --angleHor)
    {
      for (int j = 0; j < servos; j += 2)
      {
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

//функции для управления роботом
void WalkerLegs::forwardSlow(int steps = 1)
{
  directionFlag = 'f';
  for (int i = 0; i < steps; ++i)
  {
    sweepHor('l');
    sweepVer('l');
    balanceHor();
    sweepHor('r');
    sweepVer('r');
    balanceHor();
  }
}

//метод для обратной ходьбы
void WalkerLegs::backwardSlow(int steps = 1)
{
  directionFlag = 'b';
  for (int i = 0; i < steps; ++i)
  {
    sweepHor('r');
    sweepVer('l');
    balanceHor();
    sweepHor('l');
    sweepVer('r');
    balanceHor();
  }
}

//остановка робота из любого положения
void WalkerLegs::stopSlow()
{
  if (directionFlag == 'f')
  {
    sweepHor('l');
    balanceVer();
    balanceHor();
  }
  if (directionFlag == 'b')
  {
    sweepHor('r');
    balanceVer();
    balanceHor();
  }
}

//поворот налево на 90 градусов
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

//поворот направо на 90 градусов
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

//отклонение курса на малый угол налево
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

//отклонение курса на малый угол вправо
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
