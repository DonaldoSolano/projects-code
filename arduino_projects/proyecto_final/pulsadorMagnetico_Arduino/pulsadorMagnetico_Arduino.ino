
float pulsadorMagnetico = A0;
int ledPin = 13;
float knock = A1;
int lecturasKnock = 0;
int lecturasPulsador = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(pulsadorMagnetico, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(knock, INPUT);
  Serial.begin(9600);
}



void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < 5; i++)
  {
    int lecturaKnock = analogRead(knock);
    lecturasKnock = lecturaKnock + lecturasKnock;

  }
 /* for (int i = 0; i < 5; i++)
  {
    int lecturaPulsador = analogRead(pulsadorMagnetico);
    lecturasPulsador = lecturaPulsador + lecturasPulsador;
  }*/
  //lecturasPulsador = lecturasPulsador / 5;
  lecturasKnock = lecturasKnock / 5;
  if (/*lecturasPulsador >= 1000 &&*/ lecturasKnock >= 5 ) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
  /*Serial.print(lecturasPulsador);
  Serial.print("   ");*/
  Serial.print(lecturasKnock);
  Serial.println("   ");
  delay(500);
}
