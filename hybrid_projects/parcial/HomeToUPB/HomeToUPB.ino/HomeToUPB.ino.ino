const unsigned int MAX_INPUT = 90;
#define SERIALGPS Serial
#define SERIALP Serial1
#include <stdio.h>
#include <string.h>

int checksum(const char *s) {
  int c = 0;
  while (*s)
    c ^= *s++;
  return c;
}
//------------------------------------------------------------------------------------------
void setup ()
{
  //Serial.begin(115200);
  SERIALGPS.begin (115200);
  SERIALP.begin (115200);
  while (!SERIALGPS) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

} // end of setup
// here to process incoming serial data after a terminator received

void process_data (const char * data, const char * value, int valueTwo)
{
  // for now just display it
  // (but you could compare it to some value, convert to an integer, etc.)
  SERIALP.print(data);
  SERIALP.print(value);
  SERIALP.print(valueTwo, HEX);
  //SERIALP.println();
  //Serial.println(data);
}  // end of process_data
//--------------------------------------------------------------------------------------------

void processIncomingByte (const byte inByte)
{
  static char input_line [MAX_INPUT]; //buffer
  static char checksum_value[MAX_INPUT]; //buffer de checksum
  static char altitudeLatitude[MAX_INPUT]; //buffer de latitud y longitud
  static unsigned int input_pos = 0;
  static int checksum_calculado  = 0;
  static unsigned int comaCounter  = 0;
  static unsigned int in_pos = 0;
  static unsigned int in_posTwo = 0;
  //----------------------------------------------

  switch (inByte)
  {
    case '\n':   // end of text

      checksum_value [in_posTwo++] = input_line [input_pos - 2];
      checksum_value [in_posTwo++] = input_line [input_pos - 1];
      input_line [input_pos - 3] = 0;  // terminating null byte
      checksum_calculado = checksum(input_line + 1);
      // terminator reached! process input_line here ...
      process_data(altitudeLatitude, checksum_value, checksum_calculado);
      // reset buffer for next time
      input_pos = 0;
      in_pos = 0;
      comaCounter  = 0;
      in_posTwo = 0;
      break;
    case ',':
      comaCounter += 1;
      if (comaCounter >= 2 && comaCounter < 6)
      {
        input_line [input_pos++] = inByte;
        altitudeLatitude[in_pos++] = inByte;
      }
      else {
        if (input_pos < (MAX_INPUT - 1)) {
          input_line [input_pos++] = inByte;
        }
      }
      break;
    default:
      // keep adding if not full ... allow for terminating null byte
      if (input_pos < (MAX_INPUT - 1)) {
        input_line [input_pos++] = inByte;
      }
      if (comaCounter >= 2 && comaCounter < 6)
      {
        altitudeLatitude[in_pos++] = inByte;
      }
      break;
  }  // end of switch
} // end of processIncomingByte

void loop()
{
  // if serial data available, process it
  while (SERIALGPS.available () > 0) {
    processIncomingByte (SERIALGPS.read ());
  }
  // do other stuff here like testing digital input (button presses) ...
}  // end of loop
