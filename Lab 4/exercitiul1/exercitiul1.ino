#include <LiquidCrystal.h>
#include <TimerOne.h>
#include "pitches.h"

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
const int buzzerPin = 8;

int melody[] = {NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6};
int noteDurations[] = {4, 4, 4, 4, 4, 4, 4, 4};
volatile int noteIndex = 0;
volatile int animationSpeed = 500;
volatile bool updateAnimationFlag = false;

int starPosition = 0;
bool moveRight = true;

void setup() {
  lcd.begin(16, 2);
  pinMode(buzzerPin, OUTPUT);
  
  Timer1.initialize(500000);
  Timer1.attachInterrupt(timerISR);
}

void timerISR() {
  playMelody();
  updateAnimationFlag = true;
}

void loop() {
  if (updateAnimationFlag) {
    updateAnimation();
    updateAnimationFlag = false;
  }
}

void playMelody() {
  int noteDuration = 1000 / noteDurations[noteIndex];
  tone(buzzerPin, melody[noteIndex], noteDuration);
  noteIndex = (noteIndex + 1) % (sizeof(melody) / sizeof(melody[0]));
  animationSpeed = noteDuration;
}

void updateAnimation() {
  lcd.clear();

  if (moveRight) {
    starPosition++;
    if (starPosition >= 15) {
      moveRight = false;
    }
  } else {
    starPosition--;
    if (starPosition <= 0) {
      moveRight = true;
    }
  }

  lcd.setCursor(starPosition, 0);
  lcd.print('*');
}