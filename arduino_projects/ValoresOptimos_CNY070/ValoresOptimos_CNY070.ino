int Emisor = A0, ledAzul = 3, ledVerde = 5 , ledRojo = 6, valorEmisor;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Emisor, INPUT);
  pinMode(ledAzul, OUTPUT );
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT );
}

void loop() {

  valorEmisor = analogRead(Emisor);
  Serial.println(valorEmisor);
  delay(500);
  
  if (  valorEmisor >= 0 && valorEmisor < 99) {
    analogWrite(ledAzul, 0);
    analogWrite(ledVerde, 124);
    analogWrite(ledRojo, 255 );
    delay(500);

  }

  if (  valorEmisor >= 100 && valorEmisor < 159) {
    analogWrite(ledAzul, 0 );
    analogWrite(ledVerde, 247 );
    analogWrite(ledRojo, 255 );
    delay(500);

  }

  if (  valorEmisor >= 160 && valorEmisor < 249) {
    analogWrite(ledAzul, 0 );
    analogWrite(ledVerde, 255 );
    analogWrite(ledRojo, 116 );
    delay(500);

  }

  if (  valorEmisor >= 250 && valorEmisor < 349) {
    analogWrite(ledAzul, 74 );
    analogWrite(ledVerde, 237 );
    analogWrite(ledRojo, 61);
    delay(500);

  }

  if (  valorEmisor >= 350 && valorEmisor < 499) {
    analogWrite(ledAzul, 228 );
    analogWrite(ledVerde, 247 );
    analogWrite(ledRojo, 7);
    delay(500);

  }

  if (  valorEmisor >= 500 && valorEmisor < 699) {
    analogWrite(ledAzul, 247 );
    analogWrite(ledVerde, 138 );
    analogWrite(ledRojo, 7);
    delay(500);

  }
  if (  valorEmisor >= 700 && valorEmisor < 950) {
    analogWrite(ledAzul, 247 );
    analogWrite(ledVerde, 21 );
    analogWrite(ledRojo, 7);
    delay(500);

  }

}






