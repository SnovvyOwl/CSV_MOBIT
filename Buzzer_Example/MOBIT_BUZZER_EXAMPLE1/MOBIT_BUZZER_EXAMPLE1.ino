#define BUZZER 7
void setup() {
  pinMode(BUZZER,OUTPUT);
  tone(BUZZER,262); //도
  delay(1000);
  tone(BUZZER,294); //레
  delay(1000);
  tone(BUZZER,330); //미
  delay(1000);
  tone(BUZZER,349); //파
  delay(1000);
  tone(BUZZER,392); //솔
  delay(1000);
  tone(BUZZER,440); //라
  delay(1000);
  tone(BUZZER,494); //시
  delay(1000);
  tone(BUZZER,523); //도
  delay(1000);
  noTone(BUZZER);
}

void loop() {

}