#include<MsTimer2.h>
String data;
int data0 = 0;
float f=0.0;
float t=1.0;
int data2=0;
int sw=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(6,OUTPUT);
  analogWrite(6,0);
  Serial.begin(57600);
  MsTimer2::set(100,flash);
  while(Serial.available()==0);
}
void flash(void){
  analogWrite(6,data0);
  int i = analogRead(0);
  float j = i*5.0/1023.0;
  f=f+j;
  t=t+1.0;
}

void loop() {
  char aizu = Serial.read();
  if (aizu == 'a') {
    MsTimer2::stop(); //新しいduty比に変更されるまでflash関数を止め
    if(sw == 1){
      save_data();
      sw=0;
    }
    receive_duty_data();
    t=1.0;
    f=0.0;
    MsTimer2::start();
    aizu = 'c';
  }
  else if (aizu == 'b') {
    MsTimer2::stop();
    analogWrite(6, 0);
    data0=0;
    f=0;
    t=1.0;
  }
  else if(aizu == 'c'){
    if(sw == 1){
      MsTimer2::stop(); //新しいduty比に変更されるまでflash関数を止め
      aizu = 'a';
    }
    if(data2>=255){
      aizu = 'b';
    }
  }
  
}
void receive_duty_data() {
  data = Serial.readString();
  data0 = data.toInt();
  //data2=data2+data0;
  analogWrite(6, data0);
}
void save_data(){
  float y = f / t;
  Serial.print(data2);
  Serial.print(",");
  Serial.println(y);
}
