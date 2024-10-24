int latchPin = 4;
int clockPin = 7;

int dataPin = 8;  // Pinii SSD

const unsigned char ssdlut[] = { 0b00111111, 0b00000110,
                                 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101,
                                 0b00000111, 0b01111111, 0b01101111 };
const unsigned char anodelut[] = { 0b00000001, 0b00000010,
                                   0b00000100, 0b00001000 };
int num = 0;

void setup() {

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  // Cei trei pini pentru registrii
                             // de deplasare, configuraţi ca ieșire
}

void loop() {
  unsigned char digits[] = { (num % 10000) / 1000, (num % 1000) / 100, (num % 100) / 10, num % 10 };

  for (int k = 0; k < 50; k++) {
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
  }
  num = (num + 1) % 10000;
}
