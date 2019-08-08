import processing.serial.*;
import processing.net.*;

/*Monster speed variables.*/
int monsterSpeed1, monsterSpeed2, monsterSpeed3;
float monsterFrecuency1, monsterFrecuency2, monsterFrecuency3, furiousCrowdSpeed, monster1Position, monster2Position, monster3Position;
long currentMillis, previousMillis, interval;

/*We need a serial object to debug, of course*/
Serial myPort;
Client testClient;
void setup() { 
  frameRate(60);

  /*Initializing serial port*/
  myPort = new Serial(this, Serial.list()[0], 9600);
  testClient= new Client(this, "192.168.43.113", 80);
  /*Initilizing monster position variables.*/
  monsterSpeed1=0;
  monsterSpeed2=0;
  monsterSpeed3=0;

  monsterFrecuency1=0;
  monsterFrecuency2=0; 
  monsterFrecuency3=0;

  /*Initializing  furious crowd interval movement speed interval*/
  interval = 500;

  /* Setting the window size.*/
  size(1280, 720);
}
void draw() {
  for (int i = 0; i<1; i++) {
    Client clientConnected = testClient;
    if (testClient != null) {
      if (testClient.active()) {
        if (testClient.available()>0) {
          
          /*This is the event that's gonna move the monsters depend on the user pulsation frecuency*/
          switch(clientConnected.readChar())
          {
          case '1':
            monsterSpeed1+=2;
            println(clientConnected.readChar());
            break;
          case '2':
            monsterSpeed2+=2;
            println(clientConnected.readChar());
            break;
          case '3':
            monsterSpeed3+=2;
            println(clientConnected.readChar());
            break;
          }
        }
      }
    }
  }
  /*We store the elapsed time in order to use it as a value*/
  currentMillis = millis();

  /*Creating and setting the background color and alpha values, with the width and height window size values, respectively.*/
  background(width, height);

  /*Button pulsation frecuency */
  monsterFrecuency1=monsterSpeed1/1;
  monsterFrecuency2=monsterSpeed2/1;
  monsterFrecuency3=monsterSpeed3/1;

  /*Set all the monster's color to white*/
  fill(255);

  /*set all the monster's position*/
  /*If the furious crowd reach any of the monsters, the monster stops*/
  if (furiousCrowdSpeed>monster1Position)
  {
    monster1Position =-1000;
  } else {
    monster1Position=150+monsterFrecuency1;
  }
  if (furiousCrowdSpeed>monster2Position)
  {
    monster2Position =-1000;
  } else {
    monster2Position=150+monsterFrecuency2;
  }
  if (furiousCrowdSpeed>monster3Position)
  {
    monster3Position =-1000;
  } else {
    monster3Position=150+monsterFrecuency3;
  }
  /*Create all the monsters(3) as white boxes*/
  rect(monster1Position, height/3, 55, 55);//Monster 1
  rect(monster2Position, height/2, 55, 55);//Monster 2
  rect(monster3Position, (height/3)*2, 55, 55);// Monster 3

  /*Create the furious crowd as a red rectangle*/
  pushMatrix();
  fill(255, 0, 0);
  rect(furiousCrowdSpeed, height/5, 55, 500);//Monster 1

  /*We set the automatic furious crowd movement*/
  if (currentMillis-previousMillis>=interval) {
    previousMillis = currentMillis;
    furiousCrowdSpeed +=3;
  }
  popMatrix();
}
