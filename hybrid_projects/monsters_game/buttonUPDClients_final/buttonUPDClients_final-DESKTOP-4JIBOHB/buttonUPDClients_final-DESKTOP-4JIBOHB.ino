#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

/*Our WiFi configuration*/
const char* ssid = "Baddonny";
const char* password = "transhumancia";

/*Creating the udp object for communications*/
WiFiUDP udpDevice;

/*Establishing the port where the udp object it's going to receive the data*/
uint16_t localUdpPort = 4213;

/*Establishing the port where the udp object it's going to send the data*/
uint16_t UDPPort = 4210;

/*Max number of servers where the device is going to send the data*/
#define MAX_SERVERS 1

/*Establishing the server where the udp object it's going to send the data and storng it into a variable*/
const char* hosts[MAX_SERVERS] = {"192.168.43.113"};

/*In case we need to make a protocol for the data sending, this macro will serve us as a data frame limitator */
#define SERIALMESSAGESIZE 3

/*The pin where we have the button conected, defined as a macro*/
#define BUTTON 5

/*We only want to send the data once since the button is pressed so:*/
bool buttonPressed;

void setup() {
  Serial.begin(9600);//Serial communications beginning
  buttonPressed = false;
  pinMode(BUTTON, INPUT_PULLUP);//Defining the pin where the button is connected as an input.
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);//Defining the type of WiFi connection we're gonna use.
  WiFi.begin(ssid, password);//Initializing the  WiFi conection.

  /*We're going to wait until the conection it's done*/
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());
  udpDevice.begin(localUdpPort);//Initializing the udp object
}



/*This is the event that's going to trigger the udp data sending*/
void loop() {
  if (digitalRead(BUTTON) == LOW && buttonPressed == false) {
    buttonPressed = true;
    udpDevice.beginPacket(hosts[0] , UDPPort);//Send button pulsation
    udpDevice.write('3');//Setting what we're gonna send as data.
    udpDevice.endPacket();//Sending the data package.
    Serial.println("Packet sent");
  }
  if(digitalRead(BUTTON) == HIGH && buttonPressed == true)
  {
    buttonPressed = false;
    Serial.print("The button isn't being pressed: ");
    Serial.println(digitalRead(BUTTON));
  }
}
