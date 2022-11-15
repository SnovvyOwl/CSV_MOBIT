int cds = A2; //CdS 핀번호

//LED 핀번호
#define LED 8 

//주변 조도에 따른 낮밤 판단을 위한 문턱값(저항에 따라 크기가 달라짐)
#define DayLight 2


void setup() {
  Serial.begin(9600);// 조도센서의 값을 Serial로 보기
  pinMode(LED,OUTPUT); //LED OUTPUT 핀으로 설정
  pinMode(cds,INPUT);//CdS를 INPUT 핀으로 설정
}

void loop() {
  int data;
  data = analogRead(cds); // CDS로 받은 아날로그 값을 data변수로 넘겨줍니다.
  Serial.println(data); //Serial로 data값 출력, 이값으로 문턱값을 바꿔줌
  if(data<DayLight){  //어두울때
   	digitalWrite(LED,HIGH); //LED 킴
  }
  else{
  	digitalWrite(LED,LOW);//밝을때 LED 끔
  }
}