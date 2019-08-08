

// Core library for code-sense
#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif

// Prototypes


// Include application, user and local libraries
#include "SPI.h"
#include "Screen_HX8353E.h"
Screen_HX8353E myScreen;


// Define variables and constants
#define joystickY 26
uint16_t x, y, x00, y00;
uint16_t colour;
uint32_t z;


// Add setup code
void setup()
{
  Serial.begin(9600);
  myScreen.begin();
  x00 = 0;
  y00 = 0;
  myScreen.line(0, 70, 128, 70, yellowColour);
  // MSP432 14-bit set to 12-bit
}

// Add loop code
void loop()
{
  
  myScreen.dRectangle(1, y, 3, 3, blackColour);
  
  y = map(analogRead(joystickY), 0, 1023, 128, 0);
  //y = analogRead(joystickY);
  //Serial.println(y);
  //delay(500);
  myScreen.dRectangle(1, y, 3, 3, redColour);
  
  /*
  if (y < 1)      y = 1;
  if (y > 64)    y = 64;

  if (y00 != y) {
    myScreen.dRectangle(1, y00 - 1, 3, 3, redColour);
    myScreen.dRectangle(1, y - 1 , 3, 3, colour);
    x00 = x;
    y00 = y;
  }
  myScreen.gText(0, myScreen.screenSizeY() - myScreen.fontSizeY(), " y=" + i32toa(64 - (int16_t)y, 10, 1, 6),whiteColour);
*/
}


