int latchPin = 4;
int clockPin = 7;

int dataPin = 8;  // Pinii SSD

const unsigned char ssdlut[] = { 0b00111111, 0b00000110,
                                 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101,
                                 0b00000111, 0b01111111, 0b01101111 };
const unsigned char anodelut[] = { 0b00000001, 0b00000010,
                                   0b00000100, 0b00001000 };
int b1;
int b2;
int b3;

bool b1Curr = false;
bool b1Prev = false;

bool b2Curr = false;
bool b2Prev = false;

bool b3Curr = false;
bool b3Prev = false;

int startTime = 0;
int time = 0;
bool start = false;

void setup() {

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  // Cei trei pini pentru registrii
                             // de deplasare, configuraţi ca ieșire

  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);

  startTime = millis();
}

void loop() {
  b1 = digitalRead(A1);
  b2 = digitalRead(A2);
  b3 = digitalRead(A3);

  if (b1 == 0) {
    b1Curr = true;
  }
  else {
    b1Curr = false;
  }

  if (b2 == 0) {
    b2Curr = true;
  }
  else {
    b2Curr = false;
  }

  if (b3 == 0) {
    b3Curr = true;
  }
  else {
    b3Curr = false;
  }

  if(b1Curr == true && b1Prev == false) {
    if(start == false) {
      startTime = millis();
    }
    start = true;
  }

  if(b2Curr == true && b2Prev == false) {
    start = false;
  }

  if(b3Curr == true && b3Prev == false) {
    startTime = millis();
  }

  if(start == true) {
    time = (millis() - startTime) % 60000;
  }

  int sec = time / 1000;
  int hundredths = time % 1000 / 10;
  unsigned char digits[] = { sec % 100 / 10, sec % 10, hundredths / 10, hundredths % 10 };

  for (char i = 0; i <= 3; i++)  // pentru fiecare din cele 4 cifre
  {

    unsigned char digit = digits[i];          // cifra curentă
    unsigned char cathodes = ~ssdlut[digit];  // catozii
    //cifrei curente, vom nega valoarea din LUT

    digitalWrite(latchPin, LOW);  // vom activa semnalul
    //latch pentru a permite scrierea
    shiftOut(dataPin, clockPin, MSBFIRST, cathodes);  //
    //serializăm octetul anozilor
    shiftOut(dataPin, clockPin, MSBFIRST, anodelut[i]);
    // serializăm octetul anozilor
    digitalWrite(latchPin, HIGH);  // dezactivăm semnalul
    //latch
    delay(2);  // așteptare
  }

  b1Prev = b1Curr;
  b2Prev = b2Curr;
  b3Prev = b3Curr;
}
