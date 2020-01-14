#include<MsTimer2.h>
float f = 0;
void setup() {
  Serial.begin(57600);
  MsTimer2::set(10000,flash);
  while(Serial.available() == 0);
}
void flash(void){
  int i = analogRead(0);
  f = i * 5.0 / 1023.0;
  Serial.println(f);
}
void loop() {
  char aizu = Serial.read();
  if(aizu == 'a'){
    MsTimer2::stop();
    aizu = 'c';
    MsTimer2::start();
  }
  else if(aizu == 'b'){
    MsTimer2::stop();
    aizu='c';
  }
  else if(aizu == 'c'){
    //pass
  }

}
