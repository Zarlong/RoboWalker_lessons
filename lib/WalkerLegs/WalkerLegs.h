#ifndef WALKERLEGS_H
#define WALKERLEGS_H

//стандартная проверка для библиотек ардуино
// нам нужна для использования стандартных функций Ардуино
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define MAX_SERVO_COUNT 6

//Подключаем библиотеку для управления сервоприводами
#include <Servo.h>

//описание класса WalkerLegs
class WalkerLegs
{
  //публичные методы класса будут доступны пользователю для вызова
  // при использовании возможностей библиотеки в своей программе
public:
  //конструктор по умолчанию выставляет все сервы в 90градусов
  //может использоваться в скетчах при настройке робота
  WalkerLegs();

  //конструктор для конфигурации на 4 сервоприводa, с известными параметрами сервоприводов
  WalkerLegs(int a0, int a1, int a2, int a3);

  //деструктор - освобождает память при удалении объекта класса
  ~WalkerLegs();

  //методы для конфигурирования подключенных сервоприводов
  // и изменения их параметров в процессе работы программы
  void begin(int first = 7);
  void setDeviation(int dAHor = 50, int dAVer = 20);
  void setDelays(int r = 2000, int dT = 5000);

  //методы, доступные пользователю, для различных вариантов движения
  void forwardSlow(int steps = 1);
  void backwardSlow(int steps = 1);
  void stopSlow(void);
  void turnLeft(int angTurn = 36);
  void turnRight(int angTurn = 36);
  void courseDevLeft(int angTurn = 36);
  void courseDevRight(int angTurn = 36);

  //описание внутренней логики программы
  // методы и члены класса закрытые от пользователя
private:
  //объявляем сервоприводы
  int servos;
  Servo servoLegs[MAX_SERVO_COUNT];
  int servoAngle[MAX_SERVO_COUNT];
  int servoCenterConst[MAX_SERVO_COUNT];

  // Задать углы наклона для ходьбы лучше функцикей, или переменной?
  int devAngHor;
  int devAngVer;

  // переменные для углов горизонтальных осей робота
  //будут пересчитываться при вызове метода setDeviation()
  int angleHor;
  int angMinHor;
  int angMaxHor;

  // переменные для вертикальных осей робота
  //будут пересчитываться при вызове метода setDeviation()
  int angleVer;
  int angMinVer;
  int angMaxVer;

//переменные для управления задержками между действиями
  int rate;
  int delayTime;
  bool debug;
  char directionFlag;

//внутренние методы класса для совершения элементарных движений
  void debugPhase(bool debugPhase);
  void sweepVer(char dirSweep);
  void sweepHor(char dirSweep);
  void balanceHor(void);
  void balanceVer(void);
};
#endif