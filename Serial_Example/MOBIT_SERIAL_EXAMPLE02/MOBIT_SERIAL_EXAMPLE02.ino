int a; 

void setup() {
Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    a = Serial.read();
    if(a == 10){
    }
    else{
      Serial.println(a);
    }
  }
}
