#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
volatile bool start;
volatile int cntTime;
void setup() {
  start = false;
  cntTime = 0;
  lcd.begin(16, 2);
  lcd.print("Stop");
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
  if(start) {
    lcd.clear();
    lcd.setCursor(0, 0);
    int time = cntTime++;
    lcd.print(time);
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Stop");
  }
  delay(1000);
}
//prima procedură ISR
void functieDoi() {
  cntTime = 0;
}
//a doua procedură ISR
void functieUnu() {
  cntTime = 0;
  start = 1 - start;
}