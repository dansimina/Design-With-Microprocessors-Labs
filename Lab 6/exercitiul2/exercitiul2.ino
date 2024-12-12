int led = 9;         // the PWM pin the LED is attached to
int brightness = 0;  // how bright the LED is
int lightSensor = 0;

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  analogWrite(led, 255 - brightness);
  brightness = analogRead(lightSensor);
  brightness = map(brightness, 0, 1023, 0, 255);
  Serial.println(brightness);

  delay(30);
}