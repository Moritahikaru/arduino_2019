#include<MsTimer2.h>
String data;
int data0 = 0;
float f=0;
float j=0;
float y=0;
int t=1;
int data1=0;
int data2=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(6,OUTPUT);
  analogWrite(6,0);
  Serial.begin(57600);
  MsTimer2::set(100,flash);
  while(Serial.available()==0);
}
void flash(void){
  analogWrite(6,data1);
  int i = analogRead(0);
  f = i*5.0/1023.0;
  j=j+f;
  t=t+1;
}

void loop() {
  char aizu = Serial.read();
  if (aizu == 'a') {
    MsTimer2::stop(); //新しいduty比に変更されるまでflash関数を止め
    aizu = 'c';
    if(t>=10){
      save_data();
      data2=data2+10;
    }
    receive_duty_data();
    t=1;
    j=0;
    MsTimer2::start();
  }
  else if (aizu == 'b') {
    MsTimer2::stop();
    analogWrite(6, 0);
    data0=0;
    data1=0;
    j=0;
    t=1;
  }
  else if(aizu == 'c'){
    if(t>=10){
      aizu='a';
    }
    if(data2>=255){
      aizu='b';
    }
  }
  
}
void receive_duty_data() {
  analogWrite(6, data2);
}
void save_data(){
  y=j/t;
  Serial.print(data2);
  Serial.print(",");
  Serial.println(y);
  
}
