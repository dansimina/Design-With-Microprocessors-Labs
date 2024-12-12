int lightSensor = 0;
int brightness1 = 0;
int brightness2 = 0;
// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  int time1 = micros();
  brightness1 = analogRead(lightSensor);
  time1 = micros() - time1;

  int time2 = micros();
  brightness2 = read_adc(lightSensor);
  time2 = micros() - time2;

  Serial.print("Val1: ");
  Serial.print(brightness1);
  Serial.print(" Val2: ");
  Serial.print(brightness2);
  Serial.print(" Timp1: ");
  Serial.print(time1);
  Serial.print(" Timp2: ");
  Serial.println(time2);

  delay(30);
}

uint16_t read_adc(uint8_t channel) {
  ADMUX &= 0xE0;
  //șterge biții MUX0-4
  ADMUX |= channel & 0x07;  //Setează biții în MUX0-2 pentru noul
  //canal din care va trebui să citim
  ADCSRB = channel & (1 << 3);  //Setează MUX5
  ADCSRA |= (1 << ADSC);
  ADCSRA |= 0x07;
  //începe conversia
  while (ADCSRA & (1 << ADSC))
    ;  //Așteaptă până când conversia se
  //termină
  return ADCW;
}