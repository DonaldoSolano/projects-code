#include <MaxMatrix.h>  // Incluye comunicación por implementada por software con shiftOut()

// El bit mas significativo representa la parte inferior de la matriz.
const byte bulbSprite[] = {8, 8, B00000000, B00011100, B00100010, B11000010, B11000010, B00100010, B00011100, B00000000};
const byte lightBulbSprite[] = {8, 8, B00000000, B00011100, B00111110, B11111110, B11111110, B00111110, B00011100, B00000000};
const byte lightOneSprite[] = {8, 8, B00000000, B00111110, B00111110, B11111110, B11111110, B00111110, B00111110, B00000000};
const byte lightTwoSprite[] = {8, 8, B01000001, B00011100, B00111110, B11111110, B11111110, B00111110, B00011100, B01000001};

int data = 12;        // DIN, pin de envío de mensaje.
int load = 10;        // CS, SS pin de activación, equivale a selección de esclavo.
int clock = 11;       // CLK señal del reloj.
int maxInUse = 1;     // change this variable to set how many MAX7219's you'll use

MaxMatrix m(data, load, clock, maxInUse);

void setup()
{
  m.init();           // Iniciar el conjunto
  m.setIntensity(4);  // Brillo de los displays. Entre 0 y 15
}

void loop()
{
  m.writeSprite(0, 0, bulbSprite);
  delay(400);
  m.writeSprite(0, 0, lightBulbSprite);
  delay(400);
  m.writeSprite(0, 0, lightOneSprite);
  delay(400);
  m.writeSprite(0, 0, lightTwoSprite);
  delay(400);
}


