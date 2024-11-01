#include <Wire.h>

#define SLAVE_ADDRESS 8  // Adresa I2C a plăcuței slave

String receivedMessage = "";  // Mesajul primit de la slave

void setup() {
  Wire.begin();               // Inițializează ca master
  Serial.begin(9600);         // Inițializează serial pentru monitor
  delay(1000);                // Timp de inițializare
}

void loop() {
  // Trimite mesaj text către slave
  sendToSlave("Salut de la Master!");

  // Primește mesaj de la slave
  receivedMessage = receiveFromSlave();
  if (receivedMessage.length() > 0) {
    Serial.println("Mesaj de la Slave: " + receivedMessage);
  }
  
  delay(1000);  // Pauză între mesaje
}

void sendToSlave(String message) {
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(message.c_str());  // Trimite mesajul ca array de caractere
  Wire.endTransmission();
}

String receiveFromSlave() {
  String message = "";
  
  Wire.requestFrom(SLAVE_ADDRESS, 32);  // Solicită 32 bytes de la slave
  while (Wire.available()) {
    char c = Wire.read();  // Citește fiecare caracter
    message += c;
  }
  
  return message;
}


#include <Wire.h>

#define SLAVE_ADDRESS 8  // Aceeași adresă ca la master

String receivedMessage = "";  // Mesajul primit de la master

void setup() {
  Wire.begin(SLAVE_ADDRESS);  // Inițializează ca slave
  Wire.onReceive(receiveEvent);  // Configurează funcția pentru primirea de mesaje
  Wire.onRequest(requestEvent);  // Configurează funcția pentru trimiterea de răspunsuri
  Serial.begin(9600);           // Inițializează serial pentru monitor
}

void loop() {
  // Aici poți face orice altceva, codul principal al slave-ului
  delay(1000);  // Pauză între evenimente
}

// Funcție apelată când se primește un mesaj de la master
void receiveEvent(int howMany) {
  receivedMessage = "";
  while (Wire.available()) {
    char c = Wire.read();  // Citește fiecare caracter primit
    receivedMessage += c;
  }
  Serial.println("Mesaj de la Master: " + receivedMessage);
}

// Funcție apelată când masterul solicită un mesaj
void requestEvent() {
  String response = "Salut de la Slave!";
  Wire.write(response.c_str());  // Trimite răspunsul ca array de caractere
}
