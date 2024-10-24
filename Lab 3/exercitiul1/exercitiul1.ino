#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

byte clock1[8] = {
  B11111,
  B10101,
  B10101,
  B10101,
  B10001,
  B10001,
  B11111,
};

byte clock2[8] = {
  B11111,
  B10001,
  B10001,
  B10111,
  B10001,
  B10001,
  B11111,
};

byte clock3[8] = {
  B11111,
  B10001,
  B10001,
  B10101,
  B10101,
  B10101,
  B11111,
};

byte clock4[8] = {
  B11111,
  B10001,
  B10001,
  B11101,
  B10001,
  B10001,
  B11111,
};

void setup() {
  lcd.begin(16, 2);
  
  lcd.createChar(0, clock1);
  lcd.createChar(1, clock2);
  lcd.createChar(2, clock3);
  lcd.createChar(3, clock4);
  
}
// Funcţia loop rămâne nefolosită, puteți să o folosiți pentru
//a extinde funcționalitatea
void loop() {
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  delay(500);
  lcd.setCursor(0, 0);
  lcd.write(1);
  delay(500);
  lcd.setCursor(0, 0);
  lcd.write(2);
  delay(500);
  lcd.setCursor(0, 0);
  lcd.write(3);
  delay(500);
}