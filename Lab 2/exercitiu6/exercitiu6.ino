int latchPin = 4;
int clockPin = 7;

int dataPin = 8;  // Pinii SSD

const unsigned char ssdlut[] = { 0b00111111, 0b00000110,
                                 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101,
                                 0b00000111, 0b01111111, 0b01101111 };
const unsigned char anodelut[] = { 0b00000001, 0b00000010,
                                   0b00000100, 0b00001000 };
int num = 0;

int b1;
int b2;

bool b1Curr = false;
bool b1Prev = false;

bool b2Curr = false;
bool b2Prev = false;

void setup() {

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  // Cei trei pini pentru registrii
                             // de deplasare, configuraţi ca ieșire

  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
}

void loop() {
  unsigned char digits[] = { (num % 10000) / 1000, (num % 1000) / 100, (num % 100) / 10, num % 10 };

  b1 = digitalRead(A1);
  b2 = digitalRead(A2);

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

  if(b1Curr == true && b1Prev == false) {
    num = (num + 1) % 10000;
  }

  if(b2Curr == true && b2Prev == false) {
    num = max((num - 1) % 10000, 0);
  }

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
}
