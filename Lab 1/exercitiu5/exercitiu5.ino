// Citirea stării butoanelor conectate la pinii 4,5,6,7
// afișarea pe LED-uri conectate la PORTA
// variabile pentru starea butoanelor
int b1;
int b2;
int b3;
int b4;
// variabila pentru compunerea numărului de transmis
unsigned char stat = 0;
void setup() {
  // configurare pini pentru butoane, intrare
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  // activare PORTA , ca ieșire,
  DDRA = 0b11111111;
}

int a[6] = {0, 0, 0, 1, 1, 1};

int b[6];



void loop() {
  
  b[0] = a[5];
  for(int i = 1; i < 6; i++) {
    b[i] = a[i - 1];
  }

  for(int i = 0; i < 6; i++) {
    a[i] = b[i];
  }

  stat = (a[5] << 5) | (a[4] << 4) | (a[3] << 3) | (a[2] << 2) | (a[1] << 1) | a[0];
  // afișare pe LED-uri, legate la port a
  PORTA = stat;
  // așteptare 50 ms
  delay(50);
}