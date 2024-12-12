#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Dimensiuni afișaj OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1  // Nu se folosește un pin de reset extern
#define SCREEN_ADDRESS 0x3C  // Adresa I2C pentru OLED

// Inițializare afișaj OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Șiruri de caractere cu mesaje predefinite
const String SETUP_INIT = "SETUP: Initializing ESP32 dev board";
const String SETUP_ERROR = "!!ERROR!! SETUP: Unable to start SoftAP mode";
const String SETUP_SERVER_START = "SETUP: HTTP server started --> IP addr: ";
const String SETUP_SERVER_PORT = " on port: ";
const String INFO_NEW_CLIENT = "New client connected";
const String INFO_DISCONNECT_CLIENT = "Client disconnected";

const String HTTP_HEADER = "HTTP/1.1 200 OK\r\nContent-type:text/html\r\n\r\n";
const String HTML_WELCOME = "<h1>Welcome to your ESP32 Web Server!</h1>";

// Configurare WiFi
const char *SSID = "Hei hei hei";
const char *PASS = "12345678";  // Parola trebuie să aibă cel puțin 8 caractere
const int HTTP_PORT_NO = 80;

// Inițializare server HTTP pe portul 80
WiFiServer HttpServer(HTTP_PORT_NO);

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22); // Inițializare I2C pe pinii corecți pentru ESP32
  
  // Inițializare afișaj OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);  // Blochează programul dacă afișajul nu este detectat
  }

  // Șterge ecranul OLED
  display.clearDisplay();
  display.display();

  if (!WiFi.softAP(SSID, PASS)) {
    Serial.println(SETUP_ERROR);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Setup Error");
    display.display();
    while (1);  // Blochează programul dacă nu poate porni AP-ul
  }

  // Citire adresă IP a AP-ului pentru mesaj de informare
  const IPAddress accessPointIP = WiFi.softAPIP();
  const String webServerInfoMessage = SETUP_SERVER_START + accessPointIP.toString()
                                      + SETUP_SERVER_PORT + HTTP_PORT_NO;

  // Pornire server HTTP
  HttpServer.begin();
  Serial.println(webServerInfoMessage);

  // Afișare IP pe OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Server started:");
  display.println(accessPointIP.toString());
  display.display();
}

void loop() {
  WiFiClient client = HttpServer.available();  // Ascultă pentru clienți noi
  if (client) {
    Serial.println(INFO_NEW_CLIENT);

    // Afișare stare conexiune pe OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Client connected");
    display.display();

    String currentLine = "";  // Șir pentru a citi datele de la client

    while (client.connected()) {  // cât timp clientul este conectat
      if (client.available()) {  // dacă avem caractere de citit de la client
        const char c = client.read();  // citește un caracter, apoi
        Serial.write(c);  // tiparește la serial monitor

        if (c == '\n') {  // dacă caracterul este newline
          // dacă linia este goală, înseamnă finalul cererii HTTP de la client
          if (currentLine.length() == 0) {
            // Trimite mesaj de bun venit
            printWelcomePage(client);
            break;
          } else if (currentLine.startsWith("GET")) {
            // Afișează cererea GET pe OLED
            display.clearDisplay();
            display.setCursor(0, 0);
            display.println("GET request:");
            display.setCursor(0, 16);
            display.print(currentLine);
            display.display();
          }
          currentLine = "";
        } else if (c != '\r') {  // dacă există alte caractere în afară de carriage return
          currentLine += c;  // se adaugă la linia curentă
        }
      }
    }

    // Se închide conexiunea
    client.stop();
    Serial.println(INFO_DISCONNECT_CLIENT);

    // Afișează starea de deconectare pe OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Client disconnected");
    display.display();
  }
}

void printWelcomePage(WiFiClient client) {
  // Răspunsul către client trebuie să conțină headerele corecte
  client.println(HTTP_HEADER);

  // Trimitem mesajul HTML
  client.print(HTML_WELCOME);

  // Răspunsul HTTP se termină cu o linie goală
  client.println();
}
