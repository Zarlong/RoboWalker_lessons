/*
 * Эта программа с nowTime и preTime
 * где 1000 это количество секунд 
 * Автор Николай Коковкин
 * inst: @kolya_kokovkin
 */

unsigned long nowTime;
unsigned long preTime;

void setup() {
}
void loop() {
  nowTime = millis();
  if (nowTime - preTime == 1000) { // 1000 - кол секунд
    preTime = nowTime;
  }
}
