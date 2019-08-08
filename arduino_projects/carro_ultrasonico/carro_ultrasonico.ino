#include <NewPing.h>

#define E1 3
#define E2 11
#define M11 5
#define M12 6
#define M21 9
#define M22 10
#define TRIGER_PIN 12
#define ECHO_PIN 13
#define MAX_DISTANCE 200
NewPing sonar(TRIGER_PIN, ECHO_PIN, MAX_DISTANCE);
void Adelante()
{
  //Mov de un dirección
  digitalWrite(E1, HIGH);
  digitalWrite(E2, HIGH);
  digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  digitalWrite(M21, HIGH);
  digitalWrite(M22, LOW);
  delay(1000);

  //pequeña parada
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
  delay(1000);
}
void TrompoIzquierda()
{
  //Mov de un dirección
  digitalWrite(E1, HIGH);
  digitalWrite(E2, HIGH);
  digitalWrite(M11, LOW);
  digitalWrite(M12, HIGH);
  digitalWrite(M21, HIGH);
  digitalWrite(M22, LOW);
  delay(1000);

  //pequeña parada
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
  delay(1000);
}
void TrompoDerecha()
{
  //Mov de un dirección
  digitalWrite(E1, HIGH);
  digitalWrite(E2, HIGH);
  digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  digitalWrite(M21, LOW);
  digitalWrite(M22, HIGH);
  delay(1000);

  //pequeña parada
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
  delay(1000);
}
void GiroAbiertoIzquierda()
{
  //Mov de un dirección
  digitalWrite(E1, HIGH);
  analogWrite(E2, 200);
  digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  digitalWrite(M21, HIGH);
  digitalWrite(M22, LOW);
  delay(1000);

  //pequeña parada
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
  delay(1000);
}
void GiroAbiertoDerecha()
{
  //Mov de un dirección
  analogWrite(E1, 200);
  digitalWrite(E2, HIGH);
  digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  digitalWrite(M21, HIGH);
  digitalWrite(M22, LOW);
  delay(1000);

  //pequeña parada
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
  delay(1000);
}
void GiroCerradoDerecha()
{
  //Mov de un dirección
  digitalWrite(E1, HIGH);
  digitalWrite(E2, HIGH);
  digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  digitalWrite(M21, LOW);
  digitalWrite(M22, LOW);
  delay(505);

  //pequeña parada
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
  delay(1000);
}
void GiroCerradoIzquierda()
{
  //Mov de un dirección
  digitalWrite(E1, HIGH);
  digitalWrite(E2, HIGH);
  digitalWrite(M11, LOW);
  digitalWrite(M12, LOW);
  digitalWrite(M21, HIGH);
  digitalWrite(M22, LOW);
  delay(505);

  //pequeña parada
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
  delay(1000);
}
void Atras()
{
  //Mov de otra dirección
  digitalWrite(E1, HIGH);
  digitalWrite(E2, HIGH);
  digitalWrite(M11, LOW);
  digitalWrite(M12, HIGH);
  digitalWrite(M21, LOW);
  digitalWrite(M22, HIGH);
  delay(1000);

  //pequeña parada
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
  delay(500);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(M11, OUTPUT);
  pinMode(M12, OUTPUT);
  pinMode(M21, OUTPUT);
  pinMode(M22, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(50);
  Serial.print("Ping:");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");
  


}
