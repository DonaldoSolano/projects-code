#include <Adafruit_NeoPixel.h>
#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_RGB + NEO_KHZ800);

float pulsadorMagnetico = A0;
int lecturasPulsador = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(pulsadorMagnetico, INPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < 5; i++)
  {
    int lecturaPulsador = analogRead(pulsadorMagnetico);
    lecturasPulsador = lecturaPulsador + lecturasPulsador;
  }
  lecturasPulsador = lecturasPulsador / 5;
  Serial.println(lecturasPulsador);
  delay(5);
  while (lecturasPulsador > 1000) {

    for (int i = 8; i >= 0; i--) {

      for (int j = 0; j < 5; j++)
      {
        int lecturaPulsador = analogRead(pulsadorMagnetico);
        lecturasPulsador = lecturaPulsador + lecturasPulsador;
      }
      lecturasPulsador = lecturasPulsador / 5;
      Serial.println(lecturasPulsador);
      delay(5);
      strip.setPixelColor(i, strip.Color(0, 0, 255, random(255)));

      strip.show();

      delay(250);

      if (lecturasPulsador < 1000) {
        i = 0;
      }



    }
  }
  while (lecturasPulsador < 1000) {

    for (int i = 0; i < 8; i++) {

      for (int j = 0; j < 5; j++)
      {
        int lecturaPulsador = analogRead(pulsadorMagnetico);
        lecturasPulsador = lecturaPulsador + lecturasPulsador;
      }
      lecturasPulsador = lecturasPulsador / 5;
      Serial.println(lecturasPulsador);
      delay(5);
      strip.setPixelColor(i, strip.Color(0, 0, 0));

      strip.show();

      delay(250);
      if (lecturasPulsador > 1000) {
        i = 8;
      }
    }
  }

}
