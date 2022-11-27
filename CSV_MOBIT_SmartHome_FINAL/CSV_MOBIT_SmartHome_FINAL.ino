//****************** bluetooth 선언 ******************//
#include <SoftwareSerial.h>                   // 가상 시리얼 통신을 위한 라이브러리 선언
#define BT_RXD 5                              // 아두이노의 5번 핀을 RX핀 지정! 블루투스와 TX핀 연결
#define BT_TXD 4                              // 아두이노의 4번 핀을 TX핀 지정! 블루투스의 RX핀 연결
SoftwareSerial bluetooth(BT_RXD, BT_TXD);     // 블루투스 통신을 위한 설정

//****************** LCD I2C 선언 ******************//
#include <Wire.h>                             // I2C 통신을 위한 라이브러리 ===================== 깃에서 따로 받아서 라이브러리 설치 필요
#include <LiquidCrystal_I2C.h>                // LCD 1602 I2C용 라이브러리 
LiquidCrystal_I2C lcd(0x27, 16, 2);           // 접근 주소 : 0x3F or 0x27

//****************** 스마트 전등 선언 ******************//
#include <Adafruit_NeoPixel.h>                // RGB_LED 사용을 위한 라이브러리 선언 ==================== 라이브러리 설치 필요
Adafruit_NeoPixel RGB_LED = Adafruit_NeoPixel(3, 6, NEO_GRB); // 3개의 LED와 제어핀을 6번 핀으로 설정.
int R_Val, G_Val, B_Val = 0;                  // RGB_LED의 led 색상값을 저장하기 위한 변수
int R_pre,G_pre,B_pre=0;   // 이전 변수와 같은지 안같은지 확인하는 변수

//****************** 스마트 에어콘 선언 ******************//
//DHT 사용안함
//#include "DHT.h"
// #define DHTPIN 8                              // DHT11 디지털 입력 핀을 8번 핀으로 설정
// #define DHTTYPE DHT11                         // DHT11 모듈 사용 선언
//DHT dht(DHTPIN, DHTTYPE);                     // DHT 클래스 함수 선언
int fan = 11;                                 // Fan을 11번 핀으로 선언
int fan_speed = 0;                            // Fan 속도를 저장하기 위한 변수 선언
int stack = 0;                                // 전송 속도를 조절해주기 위한 변수 선언
int fan_pre=0;

//****************** 스마트 도어 선언 ******************//
#include <Servo.h>                            // 서보 라이브러리를 사용하기 위한 Servo.h 선언
Servo servo;                                  // 서보 클래스 타입인 servo 객체 선언
int servo_pin = 13;                           // 서보의 제어핀 13번 핀으로 선언
int init_angle = 178;                         // 서보의 각도 초기값
int angle = init_angle;                       // 서보의 각도를 저장하기 위한 변수
int control_num = 0;                          // 도어락의 상태를 저장하기 위한 변수

//****************** 침입자 감지 선언 ******************//
int piezo = 7;                                // 피에조 부저를 7번 핀으로 선언
int tones[] = {261, 523};                     // tones[] 배열에 원하는 음역대의 주파수를 저장.
int IRPin = 10;                               // 적외선 센서를 10번 핀으로 선언
int Caps = 0;                                 // 침입자 감지 함수로 들어가기 위한 제어변수

//****************** 스마트 가로등 ******************//
int CDS = A2;  //CDS 핀번호
int LED_Light = 9; //LED 핀번호
int cds_val;  //CDS 결과 저장용 변수
#define DAYLIGHT 5     //주변 밝기 에 대한 문턱값

void setup() {
  Serial.begin(9600);                         // PC와 아두이노간 시리얼 통신 속도를 9600bps로 설정
  bluetooth.begin(9600);                      // 블루투스와 아두이노간 시리얼 통신 속도를 9600bps로 설정
  lcd.init();                                 // LCD 모듈 초기화
  lcd.backlight();                            // LCD 모듈 백라이트 켜기

  //********* 스마트 전등 Setup() *********//
  RGB_LED.begin();                            // LED 모듈 초기화
  RGB_LED.setBrightness(100);                 // pixel의 밝기 조절 (0~255)
  RGB_LED.show();                             // 모든 픽셀 초기화 'off'

  //********* 스마트 에어콘 Setup() *********//
  //dht.begin();                                // DHT 모듈 초기화
  pinMode(fan, OUTPUT);                       // fan 핀 모드를 출력으로 설정

  //********* 스마트 도어 Setup() *********//
  servo.attach(servo_pin);                    // servo 객체를 초기화, 제어핀 선언

  //********* 침입자 감지 Setup() *********//
  pinMode(piezo, OUTPUT);                     // 피에조 핀 출력으로 설정
  pinMode(IRPin, INPUT);                      // IRPin을 입력으로 설정합니다.

  //********* 스마트 라이트 Setup() *********//
  pinMode(CDS, INPUT); //cDS핀을 인풋
  pinMode(LED_Light, OUTPUT); //LED 핀을 아웃풋
}

void loop() {
  //Serial_CON();                               // Serial 통신을 활용한 스마트홈 제어시 사용 
  Bluetooths_CON();                         // Bluetooth 통신을 활용한 스마트홈 제어시 사용
  Smart_Light(R_Val, G_Val, B_Val);           // 스마트 전등 함수 호출
  Smart_Air(fan_speed);                       // 스마트 에어컨 함수 호출
  Smart_Street_Lamp();                              // 스마트 라이트 함수 호출
  angle = Smart_Door(angle);                  // 스마트 도어 함수 호출
  if (Caps == 1) {                            // 침입자 경보시스템 사용 조건
    Smart_Alarm();                            // 이후 침입자 경보시스템 함수 호출
  }
  Serial.println("#-----------------------------------------------#");
  //lcd.clear();
}
// 이중입력 그리고 블루투스에서 나오는 값이 항상 모터를 움직이기 때문에 그걸 막기 위해 추가로 작성한코드
void setAngle(){
  
  // RGB의 과거 값이 현재 값과 같은지 안같은지판단
  // if(R_pre!=R_Val){
  //   angle=init_angle;

  // }
  // else if(G_pre!=G_Val){
  //   angle=init_angle;

  // }
  // else if(B_pre!=B_Val){
  //   angle=init_angle;
  // }
  // else if(fan_pre!=fan_speed){
  //   angle=init_angle;
  // }
  // else if (angle==0){
   if (angle==0){
    angle=init_angle; // 입력이 0을 버튼을 누를때마다 되므로 이것을 원래대로 돌려줌
  }
}
void Bluetooths_CON() {
  if (bluetooth.available()) {                // 만약 블루투스로부터 받은 통신이 있다면,
    if (bluetooth.find("R")) {                // 문자 "R" 을 검색
      R_pre=R_Val;
      R_Val = bluetooth.parseInt();           // 이후 숫자를 read와 달리 연속된 숫자로 빨강LED 값으로 저장.
      Serial.print("R"); Serial.print(R_Val);
    }
    if (bluetooth.find("G")) {                // 문자 "G" 을 검색
      G_pre=G_Val;
      G_Val = bluetooth.parseInt();           // 이후 숫자를 read와 달리 연속된 숫자로 녹색LED 값으로 저장.
      Serial.print("G"); Serial.print(G_Val);
    }
    if (bluetooth.find("B")) {                // 문자 "B" 을 검색
      
      B_pre=B_Val;
      B_Val = bluetooth.parseInt();           // 이후 숫자를 read와 달리 연속된 숫자로 파랑LED 값으로 저장.
      Serial.print("B"); Serial.print(B_Val);
    }
    if (bluetooth.find("F")) {                // 문자 "F"를 검색
      fan_pre=fan_speed;
      fan_speed = bluetooth.parseInt();       // 이후 숫자를 read와 달리 연속된 숫자로 Fan 속도로 저장.
      Serial.print("F"); Serial.print(fan_speed);
    }
    if (bluetooth.find("D")) {                // 문자 "D"를 검색
      angle = bluetooth.parseInt();           // 이후 숫자를 read와 달리 연속된 숫자로 서보모터 각도로 저장.
      control_num = 1;
      Serial.print("D"); Serial.print(angle);
    }
    setAngle();
    if (bluetooth.find("CapsON")) {           // 문자 "CapsON"를 검색
      Serial.print("CapsON");
      angle = init_angle;
      fan_speed = 0;
      R_Val = 0;
      G_Val = 0;
      B_Val = 0;
      Caps = 1;
    }

  }
}
void Serial_CON() {
  if (Serial.available()) {                // 만약 블루투스로부터 받은 통신이 있다면,
    if (Serial.find("R")) {                // 문자 "R" 을 검색
     R_pre=R_Val;
      R_Val = Serial.parseInt();           // 이후 숫자를 read와 달리 연속된 숫자로 빨강LED 값으로 저장.
      Serial.print("R"); Serial.print(R_Val);
    }
    if (Serial.find("G")) {                // 문자 "G" 을 검색
       G_pre=G_Val;
      G_Val = Serial.parseInt();           // 이후 숫자를 read와 달리 연속된 숫자로 녹색LED 값으로 저장.
      Serial.print("G"); Serial.print(G_Val);
    }
    if (Serial.find("B")) {                // 문자 "B" 을 검색
       B_pre=B_Val;
      B_Val = Serial.parseInt();           // 이후 숫자를 read와 달리 연속된 숫자로 파랑LED 값으로 저장.
      Serial.print("B"); Serial.print(B_Val);
    }
    if (Serial.find("F")) {                // 문자 "F"를 검색
       fan_pre=fan_speed;
      fan_speed = Serial.parseInt();       // 이후 숫자를 read와 달리 연속된 숫자로 Fan 속도로 저장.
      Serial.print("F"); Serial.print(fan_speed);
    }
    if (Serial.find("D")) {                // 문자 "D"를 검색
      angle = Serial.parseInt();           // 이후 숫자를 read와 달리 연속된 숫자로 서보모터 각도로 저장.
      control_num = 1;
      Serial.print("D"); Serial.println(angle);
    }
    setAngle();
    if (Serial.find("CapsON")) {           // 문자 "CapsON"를 검색
      Serial.println("CapsON");
      angle = init_angle;
      fan_speed = 0;
      R_Val = 0;
      G_Val = 0;
      B_Val = 0;
      Caps = 1;
    }
  }
}
//****************** 스마트 전등 함수 ******************//
void Smart_Light(int R, int G, int B) {       // RGB_Color 함수의 매게변수가 R,G,B로 3개이다.
  float LED_Color = RGB_LED.Color(R, G, B);   // pixel의 색 저장.
  for (int i = 0; i < 3 ; i++) {
    RGB_LED.setPixelColor(i, LED_Color);      // i와 동일한 순서의 pixel의 색을 LED_color로 지정.
    RGB_LED.show();
    delay(10);
  }
  Serial.print("R: "); Serial.print(R_Val);
  Serial.print(", G: "); Serial.print(G_Val);
  Serial.print(", B: "); Serial.println(B_Val);
}


// //****************** 스마트 에어콘 함수 ******************//
void Smart_Air(int fan_speeds) {              // 온습도 센서의 값과 불쾌지수 값을 출력하는 함수
 // float hum = dht.readHumidity();             // 습도 값을 hum 변수에 저장
 //float temp = dht.readTemperature();         // 온도 값을 temp 변수에 저장

  //float discomfort_index = ((9 * temp) / 5) - ((0.55 * (1 - (hum / 100))) * (((9 * temp) / 5) - 26)) + 32; //불쾌지수 계산식

 // Serial.print("temp : "); Serial.print((int)temp); Serial.print(" *C, ");
  //Serial.print("hum : "); Serial.print((int)hum); Serial.print(" %, ");
  //Serial.print("discomfort_index : "); Serial.println((int)discomfort_index);

  
  if (angle == init_angle) {
    lcd.clear();
    lcd.setCursor(0, 0);                                           // 커서 1번 칸, 1번 줄로 이동
    lcd.print("Eun Jeong's "); 
    lcd.setCursor(0, 1);  
    lcd.print("Sweet Home! "); 
 
  }
  if (fan_speeds > 128) {          
    analogWrite(fan, fan_speeds);                     // fan 동작
    Smart_Light(255, 000, 000);                // 스마트 전등 빨간색 출력
  }
  else {
    analogWrite(fan, fan_speeds);             // fan 동작
    Smart_Light(000, 000, 000);    
  }
}

//****************** 스마트 가로등 함수 ******************//
void Smart_Street_Lamp(){
  
  cds_val=analogRead(CDS); //CDS 데이터 읽음
  Serial.println(cds_val); // 프린트
  // CDS LOW
  if(cds_val>DAYLIGHT){
    digitalWrite(LED_Light, HIGH); // LED 끔
  }
  // CDS HIGH
  else{
    digitalWrite(LED_Light, LOW); //LED 켬
  }

}


//****************** 스마트 도어 함수 ******************//
int Smart_Door(int angles) {

 
  if (angles != init_angle) {                     // 블루투스에게 상태를 전달 받은 상황인지 아닌지 구분.
    control_num++;                            // 상태유지 카운트.
    lcd.setCursor(0, 0);
    lcd.print("Door Open Count ");
    lcd.setCursor(0, 1);
    lcd.print("       = "); lcd.print(control_num*100); lcd.print("ms ");

    if (control_num == 30) {                    // 문이 열리고 3초가 지나가는지 확인.
      control_num = 0;                        // 명령 받기 전의 상태로 복귀
      angles = init_angle;                             // 서보모터 각도 초기화.
    }
  }
  else {                                      // 대기 상태라면,
    control_num = 0;                        // 명령 받기 전의 상태로 복귀
    angles = init_angle;                             // 서보모터 각도 초기화.
  }
   
  Serial.print("angle : "); Serial.print(angles);
  Serial.print(", control : "); Serial.println(control_num);
  servo.write(angles);                        // 명령받은 각도로 서보모터 동작
  delay(100);

  return angles;                              // 조건문 이후, 각도 값을 리턴.
}


//****************** 침입자 경보시스템 함수 ******************//
//침입자 경보시스템은 강제로 무한루프에 빠뜨려 다른 기능을 먹통으로 만듬.//
void Smart_Alarm() {
  while (1) {
    Serial.println("경비시스템 작동중!!");
    lcd.setCursor(0, 0); lcd.print("Security system ");
    lcd.setCursor(0, 1); lcd.print(" IRsenser off   ");

    Smart_Light(000, 000, 000);               // 스마트 전등 "OFF"
    if (digitalRead(IRPin) == LOW) {          // 스위치 동작 확인
      Serial.println("경비시스템 침입자 발생!!!");
      lcd.setCursor(0, 0); lcd.print("!!!emergency!!! ");
      lcd.setCursor(0, 1); lcd.print(" IRsenser on    ");

      for (int i = 0; i < 2; i++) {           // for 반복문을 활용하여 i값을 0~2까지 반복
        tone(piezo, tones[i]);                // piezo핀에 tones에 저장된 주파수를 출력
        Smart_Light(000, 000, 255);           // 스마트 전등 파란색 출력
        delay(600);                           // 출력마다 0.3초의 딜레이
        Smart_Light(255, 000, 000);           // 스마트 전등 빨간색 출력
        delay(600);                           // 출력마다 0.3초의 딜레이
      }
      noTone(piezo);                          // piezo핀 초기화.
    }
    if (bluetooth.available()) {              // 만약 블루투스로부터 받은 통신이 있다면,
      if (bluetooth.find("CapsOFF")) {        // 문자 "CapsOFF"를 검색
        Smart_Light(000, 000, 000);           // 스마트 전등 "OFF"
        Caps = 0;
        break;                                // 경보시스템의 무한루프 종료.
      }
    }
    if (Serial.available()) {              // 만약 시리얼로부터 받은 통신이 있다면,
      if (Serial.find("CapsOFF")) {        // 문자 "CapsOFF"를 검색
        Smart_Light(000, 000, 000);           // 스마트 전등 "OFF"
        Caps = 0;
        break;                                // 경보시스템의 무한루프 종료.
      }
    }
    delay(10);
  }
}
