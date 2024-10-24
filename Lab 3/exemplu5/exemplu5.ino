#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
volatile int buttonVariable;
void setup() {
  buttonVariable = 0;
  lcd.begin(16, 2);
  lcd.print("A inceput");
  lcd.setCursor(0, 1);
  lcd.print("din nou");
  delay(1000);
  // cei doi pini de întrerupere, 21 și 20, declarați ca
  //intrare și rezistențe Pull-Up active
  pinMode(21, INPUT);
  pinMode(21, INPUT);
  digitalWrite(20, HIGH);
  digitalWrite(21, HIGH);
  // atașăm pinilor 21 și 21, corespunzători INT1 și INT0,
  //funcţii ISR
  attachInterrupt(digitalPinToInterrupt(20), functieUnu,
                  RISING);
  attachInterrupt(digitalPinToInterrupt(21), functieDoi,
                  CHANGE);
}
void loop() {
  //aici sunt taskuri care se execută în mod normal cînd se
  //rulează programul
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Programul principal");
  delay(1000);
}
//prima procedură ISR
void functieDoi() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Functia Doi");
}
//a doua procedură ISR
void functieUnu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Functia Unu");
}