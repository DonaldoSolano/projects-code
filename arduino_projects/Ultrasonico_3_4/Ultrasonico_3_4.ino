#include <pitches.h>
#define echoPin 9 // Echo Pin
#define trigPin 8 // Trigger Pin
#define BuzzerPin 7 // Onboard LED
#define cantidadLecturas 5
int ledPin = 3;
int ledPin2 = 5;
int ledPin3 = 6;

float potenciometerValue ;
float cambioPotenciometerValue;

int maximumRange = 100; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
int promedio;
long suma = 0;
float  iluminacionLeds;

int offMusic [][2] =
{
  {NOTE_C4, 3},
  {NOTE_C2, 1},
  {0, 6},
  {NOTE_C1, 1}
};

int onMusic[][2] = {
  {NOTE_E5, 1},
  {NOTE_D5, 1},
  {NOTE_D5, 2},
  {NOTE_G5, 4}
};

void playMelody( int partiture[][2], int partitureLength, int pinBuzer, int timeBeat )
{
  
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < partitureLength; thisNote++) {
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = timeBeat / (partiture[thisNote][1]);
    tone(pinBuzer, (partiture[thisNote][0]), noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(pinBuzer);
  }
}

long lectura()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  distance = duration / 58.2;
  delay(50);
}

void iluminacion()
{
  if (suma <= maximumRange && suma > minimumRange)
  {
    iluminacionLeds = map(constrain(suma, 0, 100), 0, 100, 0, 255);
    analogWrite(ledPin, iluminacionLeds);
    analogWrite(ledPin2, iluminacionLeds);
    analogWrite(ledPin3, iluminacionLeds);
    delay(200);
  }
  else
  {
    analogWrite(ledPin, LOW);
    analogWrite(ledPin2, LOW);
    analogWrite(ledPin3, LOW);
  }

}


void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(BuzzerPin, OUTPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop() {


  int i = 0;
  for (i = 0 ; i <= 4; i++)
  {
    lectura();
    suma += distance;

  }
  suma = suma / 5;
  iluminacion();
  if (suma <= maximumRange && suma > minimumRange) {
    /* Send a negative number to computer and Turn LED ON
      to indicate "out of range" */

    playMelody(offMusic, 4, BuzzerPin, 200);
    //digitalWrite(BuzzerPin, LOW);
  }
  else
  {
    playMelody(onMusic, 3, BuzzerPin, 100);
    digitalWrite(BuzzerPin, LOW);
  }
  Serial.println(suma);

  suma = 0;

}
