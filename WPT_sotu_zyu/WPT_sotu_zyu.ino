#include<MsTimer2.h>
float f = 0;
String data;
float data0 = 0;
void setup() {
  Serial.begin(57600);
  MsTimer2::set(100,flash);
  while(Serial.available() == 0);
}
void flash(void){
  int i = analogRead(0);
  f = i * 5.0 / 1023.0;
  Serial.println(f,4);
  //有効数字を4桁にする．
  //シリアルモニターは初期設定では小数第二位までしか読み取れないから.
}
void loop() {
  char aizu = Serial.read();
  if(aizu == 'a'){
    MsTimer2::stop();
    aizu = 'c';
    receive_duty_data();
    MsTimer2::start();
  }
  else if(aizu == 'b'){
    MsTimer2::stop();
    aizu='c';
  }

}
void receive_duty_data() {
  
  data = Serial.readString();
  data0 = data.toFloat();
}
