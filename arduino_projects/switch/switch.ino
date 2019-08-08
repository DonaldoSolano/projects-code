int Button = 4;
int ButtonDos = 2;
int ledPin = 13;
int buttonState = 0;
int buttonStateDos = 0;
int lastButtonState = 0;
int lastButtonStateDos = 0;
bool encendido = false;


void setup()
{
  pinMode (ledPin, OUTPUT);
  pinMode (Button, INPUT);
  pinMode (ButtonDos, INPUT);
}
void loop ()
{

  buttonState = digitalRead(Button);
  buttonStateDos = digitalRead(ButtonDos);
  
     if (!encendido == true)
  {
    digitalWrite(ledPin, HIGH);
  }
  else (!encendido == false);
  {
    digitalWrite(ledPin, LOW);
  }
  
  if (buttonState != lastButtonState || buttonStateDos != lastButtonStateDos)
  {
    encendido = !encendido;

  }

  lastButtonState = buttonState;
  lastButtonStateDos = buttonStateDos;

}
