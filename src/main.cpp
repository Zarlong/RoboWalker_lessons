#include <Arduino.h>
#include <WalkerLegs.h>

WalkerLegs hutOnChickenLegs(87, 89, 86, 82);

void setup() 
{
  hutOnChickenLegs.begin(); // включаем монитор порта
  hutOnChickenLegs.setDelays(10, 100);
}
void loop() 
{
hutOnChickenLegs.forwardSlow(5);
hutOnChickenLegs.stopSlow();          //  1 функция - движения вперёд  
//hutOnChickenLegs.courseDevRight(36);  
//hutOnChickenLegs.stopSlow();              
hutOnChickenLegs.turnRight(90);        //  2 функция - движения назад
hutOnChickenLegs.stopSlow();             //  3 функция - остановка
}