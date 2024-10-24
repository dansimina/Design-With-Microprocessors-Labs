//includem fișierul cu definițiile pentru tonuri
#include "pitches.h"
// melodia ca lista de note
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3,
  NOTE_C4
};
//introducem durata pentru fiecare notă din melodie
int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };
void setup() {
  //pentru fiecare notă din vectorul melody
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    //calculăm durata de afișare a notei
    int noteDuration = 1000 / noteDurations[thisNote];
    //apelăm funcția de tone pentru difuzorul atașat la
    //pinul 8 și durata specificată
    tone(8, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
}
void loop() {
}