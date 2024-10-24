int buzerPin = 8;  //pinul la care atașăm generatorul de sunete
int puls = 0;
// factorul de umplere, inițial 0
int pas = 10;     // pasul de incrementare al factorului de umplere
int ledPin = 13;  //ledul de pe placă
void setup() {
  // declararea pinilor ca ieșire
  pinMode(buzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}
void loop() {
  // setăm factorul de umplere al buzerului și al ledului
  analogWrite(buzerPin, puls);
  analogWrite(ledPin, puls);
  // modificăm pwm-ul pentru următoarea iterație
  puls = puls + pas;
  // schimbăm direcția la capetele intervalului: din
  //incrementare devine decrementare și invers
  if (puls <= 0 || puls >= 255) {
    pas = -pas;
  }
  // un mic delay pentru a vedea efectul
  delay(30);
}