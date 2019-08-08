int S1 = 3;
int ledPin = 13;
int Press = 0;
int potenciometro = A0;
int numeroSecreto = 50;
bool presionado;

void setup() {
  pinMode(S1, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(potenciometro, INPUT);
  Serial.begin (9600);
  potenciometro = map(numeroSecreto, 0, 1023 , 0, 255);
}

void loop() {
  Press = digitalRead(S1);
  potenciometro = analogRead(A0);
  if (!Press) {
    presionado = true;
    if (potenciometro > 20 && potenciometro < 40 && presionado == true) {



      digitalWrite(ledPin, HIGH);
      Serial.println ("Adivinaste el número");
      delay (1000);
      digitalWrite(ledPin, LOW);
      presionado = false;
    }
    else
    {
      Serial.println ("Sigue Intentando");
      delay (1000);
    }
  }
}     

