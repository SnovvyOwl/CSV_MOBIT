#define answer 53 // 아스키 코드 5

void setup() {
  Serial.begin(9600); // 말하는 속도 조절
  Serial.println("3 + 2 = ?");
}

void loop() {
  if(Serial.available()) { // 어떤 소리가 들려오면
    int a = Serial.read(); // 소리를 듣고 저장한다.

    if(a == answer){ // 올바른 정답을 입력했을 때
      Serial.println("correct");
    }
    else if(a == 10){ // 쓰레기 값 처리
    }
    else{ // 오답을 입력했을 때
      Serial.println("not correct");
    }

  }
}
