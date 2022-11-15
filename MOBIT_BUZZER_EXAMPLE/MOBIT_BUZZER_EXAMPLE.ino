#define BUZZER 7 // Buzzer Pin을 7번으로 쓰겠습니다.
void setup()
{
  pinMode(BUZZER, OUTPUT); //Buzzer 핀 설정
}

void loop()
{
  tone(BUZZER,3520);   //BUZZER를 3520hz(A7)을 (높고 높은 라)
  delay(200);               //200ms 대기
  tone(BUZZER,2794);   //BUZZER를 2794hz(F7)을 (높고 높은 파)
  delay(200);
}
