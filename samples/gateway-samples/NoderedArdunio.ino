/**
 * This Arduino Sketch is written to demonstrate the Gateway Support in 
 * IBM Watson IoT Platform, and this sketch represents the device code 
 * that connects to Raspberry Pi Gateway.
 *     
 */
 
char deviceEvent[30]="";
// LED PIN is 13
const int LEDPIN = 13;

void setup() {
  Serial.begin(9600);
  pinMode(LEDPIN,OUTPUT); // LED actuator  
  delay(500);
}

/**
 * This method does the following,
 * 
 * 1. Listen for the command from the Gateway (raspberry Pi) and glow LED which is connected to the PIN 13
 * 2. Sends the temperature status to the Gateway in the following format,
 * 
 *    { "temp" : n }
 *   
 *      
 */
  
void loop() {
  if (Serial.available()) {
    int value = Serial.parseInt();
    // Sometime we see a garbage number, so restrict to a lower number
    if(value > 100) {
        value = 5;
    }
    blink(value);
  } 

  strcpy(deviceEvent, "");
  
  char val[10];
  strcat(deviceEvent,"{\"temp\":");
  dtostrf(getTemp(),1,2, val);
  strcat(deviceEvent,val);
  strcat(deviceEvent,"}");
  Serial.println(deviceEvent);
  delay(2000);
}

void blink(int n){
  for (int i = 0; i < n; i++) {
    digitalWrite(LEDPIN, HIGH);
    delay(100);
    digitalWrite(LEDPIN, LOW);
    delay(100);
  }
}

/*
This function is reproduced as is from Arduino site => http://playground.arduino.cc/Main/InternalTemperatureSensor
*/
double getTemp(void) {
  unsigned int wADC;
  double t;
  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
  ADCSRA |= _BV(ADEN); // enable the ADC
  delay(20); // wait for voltages to become stable.
  ADCSRA |= _BV(ADSC); // Start the ADC
  // Detect end-of-conversion
  while (bit_is_set(ADCSRA,ADSC));
  // Reading register "ADCW" takes care of how to read ADCL and ADCH.
  wADC = ADCW;
  // The offset of 324.31 could be wrong. It is just an indication.
  t = (wADC - 324.31 ) / 1.22;
  // The returned temperature is in degrees Celcius.
  return (t);
}
