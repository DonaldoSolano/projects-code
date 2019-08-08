const int ledPin = 13;      // LED connected to digital pin 13
const int knockSensor = A0; // the piezo is connected to analog pin 0



// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin


void setup() {

  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
  Serial.begin(9600);       // use the serial port
  pinMode(knockSensor, INPUT);
}

void loop() {
  // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(knockSensor);
  int iluminacion = map(sensorReading, 0, 1023, 0, 255);
  // if the sensor reading is greater than the threshold:
  
    // toggle the status of the ledPin:

    // update the LED pin itself:
    digitalWrite(ledPin, iluminacion);

   
    
  
}

