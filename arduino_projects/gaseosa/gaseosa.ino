int Button = 2;
int Button2 = 3;
int ledPin = 13;
int Press = 0;
int Press1 = 0;
bool sePresiono = false;

void setup() {
  pinMode(Button, INPUT);
  pinMode(Button2, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin (9600);
}

void loop() {
  Press = digitalRead(Button);
  Press1 = digitalRead(Button2);

  if (!Press) {
    Serial.println ("Gaseosa Llena");
    delay (1000);
    sePresiono = true;
  }
  if (!Press1 && sePresiono == true)
  {
    Serial.println ("Gaseosa Tapada");
    delay (1000);
    digitalWrite(ledPin, HIGH);
    Serial.println ("Gaseosa Bien Empacada");
  }
}

