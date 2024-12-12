#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  
#define SCREEN_HEIGHT 64  
#define OLED_RESET -1     

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const String SETUP_INIT = "SETUP: Initializing ESP32 dev board";
const String SETUP_ERROR = "!!ERROR!! SETUP: Unable to start SoftAP mode";
const String SETUP_SERVER_START = "SETUP: HTTP server started --> IP addr: ";
const String INFO_NEW_CLIENT = "New client connected";
const String INFO_DISCONNECT_CLIENT = "Client disconnected";
const String HTTP_HEADER = "HTTP/1.1 200 OK\r\nContent-type:text/html\r\n\r\n";
const String HTML_WELCOME = "<h1>SALUT!</h1>";
const char *SSID = "ceva";
const char *PASS = "12345678";
const int HTTP_PORT_NO = 80;
const int LED_PIN = 2;  

WiFiServer HttpServer(HTTP_PORT_NO);

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED init failed"));
    while (1);  
  }
  display.clearDisplay();
  display.setTextSize(2);  
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Starting ESP32...");
  display.display();
  delay(2000);  

  if (!WiFi.softAP(SSID)) {
    Serial.println(SETUP_ERROR);
    display.clearDisplay();
    display.println("AP Mode Error!");
    display.display();
    while (1);
  }

  IPAddress accessPointIP = WiFi.softAPIP();
  String webServerInfoMessage = SETUP_SERVER_START + accessPointIP.toString() + " on port: " + HTTP_PORT_NO;
  HttpServer.begin();
  Serial.println(webServerInfoMessage);
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Server started!");
  display.print("IP: ");
  display.println(accessPointIP);
  display.display();
  delay(2000);  
}

void loop() {
  WiFiClient client = HttpServer.available();
  if (client) {
    Serial.println(INFO_NEW_CLIENT);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Client connected:");
    display.display();
    delay(1000);  
    String currentLine = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            printWelcomePage(client);
            break;
          } else if (currentLine.startsWith("GET")) {
            display.clearDisplay();
            display.setCursor(0, 0);
            display.println("GET Request:");
            display.println(currentLine);
            display.display();
            delay(2000);  

            if (currentLine.indexOf("/LedOn") >= 0) {
              digitalWrite(LED_PIN, HIGH);  
              display.clearDisplay();
              display.setCursor(0, 0);
              display.println("LED is ON");
              display.display();
            } else if (currentLine.indexOf("/LedOff") >= 0) {
              digitalWrite(LED_PIN, LOW);  
              display.clearDisplay();
              display.setCursor(0, 0);
              display.println("LED is OFF");
              display.display();
            }
          }
          currentLine = "";
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    client.stop();
    Serial.println(INFO_DISCONNECT_CLIENT);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Client disconnected");
    display.display();
    delay(1000);  
  }
}

void printWelcomePage(WiFiClient client) {
  client.println(HTTP_HEADER);
  client.print(HTML_WELCOME);
  client.println();
}
