#include<SoftwareSerial.h>
#include<string.h>
#define TX 4
#define RX 5
SoftwareSerial bluetooth(TX,RX);
uint8_t random_num;
int data=65355;
void setup(){
  randomSeed(analogRead(0));
  random_num=random(2048);
  Serial.begin(9600);
  bluetooth.begin(9600);

  Serial.println("AT setup");
  bluetooth.write(String("AT").c_str());

  delay(500);
  while(1){
      data=bluetooth.read();
      if (data==-1){
        Serial.write('\n');
        break;
      }
      Serial.write(data);
  }


  bluetooth.write(String("AT+NAME?").c_str());
  delay(500);
  data=65355;
  while(1){
      data=bluetooth.read();
      if (data==-1){
        Serial.write('\n');
        break;
      }
      Serial.write(data);
  }

  bluetooth.write((String("AT+NAME MOBIT")+String(random_num)).c_str());
  delay(500);
  data=65355;
  while(1){
      data=bluetooth.read();
      if (data==-1){
        Serial.write('\n');
        break;
      }
      Serial.write(data);
  }
}
 
void loop(){
  if(Serial.available()){
    bluetooth.write(Serial.read());
  }
  if(bluetooth.available()){
    Serial.write(bluetooth.read());
  }
}