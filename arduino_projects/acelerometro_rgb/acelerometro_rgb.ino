int colorRojo = 3;
int colorVerde = 5;
int colorAzul = 6;
int xpin = A0;
int ypin = A1;
int zpin = A2;
int numberOfSensorReads = 6;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(colorRojo, OUTPUT);
  pinMode(colorVerde, OUTPUT);
  pinMode(colorAzul, OUTPUT);

  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(zpin, INPUT);
}
/*void prendeRGB(int _R, int _G, int _B)
{
  analogWrite (colorRojo , _R);

  analogWrite (colorVerde, _G);

  analogWrite (colorAzul, _B);
  //colorRojo = random(256);
  //colorVerde = random(256);
  //colorAzul = random(256);

}*/

void Potenciometro()
{
  int xAccel = 0, yAccel = 0, zAccel = 0;
  for (int i = 0; i < numberOfSensorReads; ++i)
  {
    // It takes 100 us (0.0001 s) to read an analog input
    xAccel += analogRead(xpin);
    yAccel += analogRead(ypin);
    zAccel += analogRead(zpin);
  }

  xAccel /= numberOfSensorReads;
  yAccel /= numberOfSensorReads;
  zAccel /= numberOfSensorReads;

  // print the sensor values:

  Serial.print("x: ");
  Serial.print(xAccel);
  Serial.print(" | y: ");
  Serial.print(yAccel);
  Serial.print(" | z: ");
  Serial.println(zAccel);
  if (xAccel >= 400) {
    analogWrite (colorRojo , 200);

  analogWrite (colorVerde, 0);

  analogWrite (colorAzul, 200);
    //prendeRGB (colorRojo, colorVerde, colorAzul);
    delay (100);
  }
  if (yAccel >= 400) {
    analogWrite (colorRojo , 200);

  analogWrite (colorVerde, 230);

  analogWrite (colorAzul, 0);
   // prendeRGB (colorRojo, colorVerde, colorAzul);
    delay (100);
  }
  if (zAccel >= 400) {
    analogWrite (colorRojo , 0);

  analogWrite (colorVerde, 230);

  analogWrite (colorAzul, 200);
    //prendeRGB (colorRojo, colorVerde, colorAzul);
    delay (100);
  }

}
void loop() {
  // put your main code here, to run repeatedly:



  Potenciometro();
  // Slow down the serial output - Easier to read

}
