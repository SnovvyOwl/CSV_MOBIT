#include <Wire.h> // i2C 통신을 위한 라이브러리                   
#include <LiquidCrystal_I2C.h>            // LCD 1602 I2C용 라이브러리 
LiquidCrystal_I2C lcd(0x27, 16, 2);       // 접근주소: 0x3F or 0x27 16개 열 2개행

void setup()
{
  lcd.init();  // LCD 초기화
}

void loop()
{
  lcd.backlight();                        // 백라이트 켜기
  lcd.setCursor(0, 0);                     // 0번째, 0라인
  lcd.print("Eun Jung's ");
  lcd.setCursor(0, 1);                       // 1번째, 1라인
  lcd.print("Sweet Home!");
  
  delay(1000); // 1초 뒤
  lcd.clear(); // 전체 LCD 비우기
  
  
  lcd.setCursor(0, 0);
  lcd.print("Security Mode on");
  lcd.setCursor(0, 1);                       // 1번째, 1라인
  lcd.print("Nothing Strange");
  
  delay(1000); // 1초 뒤
  lcd.clear(); // 전체 LCD 비우기
}