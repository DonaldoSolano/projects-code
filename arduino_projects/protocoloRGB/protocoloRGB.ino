// the possible states of the state-machine
typedef enum states {  NONE, VALUE_R, VALUE_G, VALUE_B, CHECKSUM } ;

// current state-machine state
states state = NONE;
// current partial number
size_t dataCapacity;
uint8_t  R, G, B, C; //unsigned int
uint8_t currentValue; //unsigned int
#define ledR 9
#define ledG 10
#define ledB 11
void setup ()
{
  Serial.begin (9600);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  state = NONE;

}  // end of setup

uint8_t XORChecksum8(const byte *data, size_t dataLength)
{
  uint8_t value = 0;
  for (size_t i = 0; i < dataLength; i++)
  {
    value ^= (uint8_t)data[i];
  }
  return ~value;
  value = C;
}

void turnLedOn()
{
  analogWrite(9, R );
  analogWrite(10, G );
  analogWrite(11, B );
  Serial.print(R, " ");
  Serial.print(' ');
  Serial.print(G, " ");
  Serial.print(B, " ");
  Serial.println();
}
void processR (uint8_t value) //const unsigned int
{
  // do something with RPM
  Serial.print ("R = ");
  Serial.println (value);
  dataCapacity = R;
  R = value;
  dataCapacity = R;
}

void processG (uint8_t value)//const unsigned int
{
  // do something with speed
  Serial.print ("G = ");
  Serial.println (value);
  G = value;
  dataCapacity = G;
}

void processB (uint8_t value)//const unsigned int
{
  // do something with gear
  Serial.print ("B = ");
  Serial.println (value);
  B = value;
  dataCapacity = B;
}

void handlePreviousState ()
{
  switch (state)
  {
    case VALUE_R:
      processR (currentValue);
      break;
    case VALUE_G:
      processG (currentValue);
      break;
    case VALUE_B:
      processB (currentValue);
      break;
    case CHECKSUM:
      XORChecksum8 (currentValue, dataCapacity);
      break;
  }  

  currentValue = 0;
  dataCapacity = 0;
}  

void processIncomingByte (int8_t c) //const byte
{
  if (isdigit (c))
  {
    currentValue *= 10;
    currentValue += c - '0';
  }  // end of digit
  else
  {

    // The end of the number signals a state change
    handlePreviousState ();

    // set the new state, if we recognize it
    switch (c)
    {
      case 'R':
        state = VALUE_R;
        break;
      case 'G':
        state = VALUE_G;
        break;
      case 'B':
        state = VALUE_B;
        break;
      case 'C':
        state = CHECKSUM;
        break;
      default:
        state = NONE;
        break;
    }
  }

}

void loop ()
{
  while (Serial.available ())
    processIncomingByte (Serial.read ());

  // do other stuff in loop as required
  turnLedOn();
}  // end of loop
