#include <Servo.h>

//переменные для чтения информации из монитора порта
String strData = "";
boolean recievedFlag;
int intVar;

//параметры сервопривода
const int servos = 4;// количество сервоприводов в механизме

//переменные для углов горизонтальных осей робота
int angleHor = 90;
int devAngHor = 35;
int angMinHor = angleHor - devAngHor;
int angMaxHor = angleHor + devAngHor;

//переменные для вертикальных осей робота
int angleVer = 90;
int devAngVer = 20;
int angMinVer = angleVer - devAngVer;
int angMaxVer = angleVer + devAngVer;

//параметры сервоприводов
// сюда записываем полученные показатели среднего положения сервоприводов
const int servoCenterConst[servos] = {87, 89, 86, 82};
int servoAngle[servos];
Servo servoLegs[servos];
int rate = 5;
int delayTime = 100;
bool debug = true;
char directionFlag = 's';


void DebugPhase(bool debugPhase) {
  if (debugPhase == true) {
    delay(delayTime);
  }
}



//функция для шага вперёд
void SweepVer(char dirSweep) {
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

//функция для возвращения в исходное положение
void BalanceVer() {
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



//функция для отклонения вбок
void SweepHor(char dirSweep) {
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

//функция для возвращения в исходное положение
void BalanceHor() {
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

void ForwardSlow(int steps = 1) {
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

void BackwardSlow(int steps = 1) {
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

void StopSlow() {
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
  SweepHor('l');
  for (servoAngle[1]; servoAngle[1] <= servoCenterConst[1] + angTurn; ++servoAngle[1]) {
    servoLegs[1].write(servoAngle[1]);
    delay(rate);
  }
  BalanceHor();

  //вторая фаза
  SweepHor('r');
  for (servoAngle[3]; servoAngle[3] <= servoCenterConst[3] + angTurn; ++servoAngle[3]) {

    servoAngle[1] -= 1;

    servoLegs[1].write(servoAngle[1]);
    servoLegs[3].write(servoAngle[3]);
    delay(rate);
  }
  BalanceHor();

  //третья фаза
  SweepHor('l');
  for (servoAngle[1]; servoAngle[1] <= servoCenterConst[1] + angTurn; ++servoAngle[1]) {

    servoAngle[3] -= 1;
    servoLegs[1].write(servoAngle[1]);
    servoLegs[3].write(servoAngle[3]);
    delay(rate);
  }
  BalanceHor();

  //четвертая  фаза
  SweepHor('r');
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

void CourseDevLeft(int angTurn = 36) {

  //первая фаза
  SweepHor('l');
  for (servoAngle[1]; servoAngle[1] <= servoCenterConst[1] + angTurn; ++servoAngle[1]) {
    servoLegs[1].write(servoAngle[1]);
    delay(rate);
  }
  BalanceHor();


  //четвертая  фаза
  SweepHor('r');
  for (servoAngle[1]; servoAngle[1] >= servoCenterConst[1]; --servoAngle[1]) {
    servoLegs[1].write(servoAngle[1]);
    delay(rate);
  }
  BalanceHor();
}


void CourseDevRight(int angTurn = 36) {

  //первая фаза
  SweepHor('r');
  for (servoAngle[3]; servoAngle[3] >= servoCenterConst[3] - angTurn; --servoAngle[3]) {
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

void setup() {
  Serial.begin(9600); // включаем монитор порта
  int iter = 0; //счетчик сервоприводов (начинается с нуля)

  //инициализируем сервоприводы
  for (int i = 0; i < servos; ++i) {
    servoAngle[i] = servoCenterConst[i];         //заполняем новый, изменяемый массив для хранения текущего положения сервоприводов
    servoLegs[i].attach(i + 7);                  //инициализируем порты с сервоприводами
    servoLegs[i].write(servoCenterConst[i]);      //выставляем начальное положение сервопривода
    delay(1000);
  }
}


void loop() {
  //итоговая версия основного цикла стала намногоболее удобна для работы и понимания
  //  ForwardSlow();          //  1 функция - движения вперёд  
  //  BackwardSlow();         //  2 функция - движения назад
  //  StopSlow();             //  3 функция - остановка
  //  TurnLeft();             //  4 функция - поворот на 90 градусов налево  
  //  TurnRight();            //  5 функция - поворот на 90 градусов направо
  
  CourseDevLeft();            //  6 функция - отклонение курса налево
  CourseDevRight();           //  7 функция - отклонение курса направо
}
