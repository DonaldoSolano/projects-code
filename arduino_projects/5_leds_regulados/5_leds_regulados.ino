int ledPin  = 2;
int ledPin2 = 3;
int ledPin3 = 4;
int ledPin4 = 5;
int ledPin5 = 6;
int potenciometro = A0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(potenciometro, INPUT);
}

void loop() {
  potenciometro = analogRead(A0);
  if (potenciometro > 1 && potenciometro < 1023) {
    digitalWrite(ledPin, HIGH);

    if (potenciometro > 5 && potenciometro < 1023) {
      digitalWrite(ledPin2, HIGH);

      if (potenciometro > 10 && potenciometro < 1023) {
        digitalWrite(ledPin3, HIGH);

        if (potenciometro > 15 && potenciometro < 1023) {
          digitalWrite(ledPin4, HIGH);

          if (potenciometro > 20 && potenciometro < 1023) {
            digitalWrite(ledPin5, HIGH);

          }
          else {
            digitalWrite(ledPin5, LOW);
          }
        }
        else {
          digitalWrite(ledPin4, LOW);
        }
      }
      else {
        digitalWrite(ledPin3, LOW);
      }

    }
    else {
      digitalWrite(ledPin2, LOW);
    }

  } else {
    digitalWrite(ledPin, LOW);
  }
}
