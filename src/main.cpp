// #include <Arduino.h>
#include "WalkerLegs.h"

// WalkerLegs hutOnChickenLegs(87, 89, 86, 82);    //black
// WalkerLegs hutOnChickenLegs(89, 92, 82, 96);    //yellow
// WalkerLegs hutOnChickenLegs(87, 83, 89, 79, 80, 100);    //astartes
WalkerLegs hutOnChickenLegs(90, 89, 91, 90);    //your robot


void setup()
{
  // включаем монитор порта
  Serial.begin(9600);
  //инициализируем сервоприводы
  hutOnChickenLegs.begin();
  hutOnChickenLegs.setDelays(5, 200);

  hutOnChickenLegs.forwardSlow(1);
  hutOnChickenLegs.stopSlow();

  hutOnChickenLegs.setDelays(6, 300);


  hutOnChickenLegs.turnRight();

  hutOnChickenLegs.setDelays(5, 200);

  hutOnChickenLegs.forwardSlow(2);
  hutOnChickenLegs.stopSlow();

hutOnChickenLegs.setDelays(6, 300);

  hutOnChickenLegs.turnLeft();

  hutOnChickenLegs.setDelays(5, 200);

  hutOnChickenLegs.forwardSlow(6);
  hutOnChickenLegs.stopSlow();

hutOnChickenLegs.setDelays(6, 300);

  hutOnChickenLegs.turnLeft();

hutOnChickenLegs.setDelays(5, 200);

  hutOnChickenLegs.forwardSlow(2);
  hutOnChickenLegs.stopSlow();

hutOnChickenLegs.setDelays(6, 300);

  hutOnChickenLegs.turnRight();

  hutOnChickenLegs.setDelays(5, 200);

  hutOnChickenLegs.forwardSlow(5);
  hutOnChickenLegs.stopSlow();

  hutOnChickenLegs.setDelays(1, 25);

  hutOnChickenLegs.turnLeft();
}

//главный цикл
void loop()
{
  //hutOnChickenLegs.forwardSlow(2);
 // hutOnChickenLegs.stopSlow();

  //hutOnChickenLegs.turnLeft();

  //hutOnChickenLegs.forwardSlow(2);
  //hutOnChickenLegs.stopSlow();

//  hutOnChickenLegs.courseDevRight();

//  hutOnChickenLegs.forwardSlow(2);
//  hutOnChickenLegs.stopSlow();

//  hutOnChickenLegs.turnRight();

//  hutOnChickenLegs.forwardSlow(2);
  //hutOnChickenLegs.stopSlow();

//  hutOnChickenLegs.courseDevLeft();

  
}