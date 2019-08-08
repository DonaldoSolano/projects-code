/*Importing libraries*/
#include <WiFiUdp.h>
#include <WiFi.h>
#include <WiFiMulti.h>

/*Here we create the TCP/IP object*/
WiFiMulti wifiMulti;

/*Establishing the max number of clients that can be connected to the server*/
#define MAX_SRV_CLIENTS 1

/*Setting the port where we are going to listen for the requests in the TCP/IP conection*/
WiFiServer server(80);

/*Creating the the array of clients that we are going to use to send and receive data to the high level client(processing sketch)*/
WiFiClient serverClients[MAX_SRV_CLIENTS];

/*Setting our WiFi configuration*/
const char* ssid = "Baddonny";
const char* password = "transhumancia";

/*Creating udp object to send and receive data*/
WiFiUDP udpDevice;

/*Establishing the port where we are going to receive the data*/
uint16_t localUdpPort = 4210;

void setup() {
  //Serial.begin(9600);
  //Serial.println();
  //Serial.println();
  //Serial.print("Connecting to ");
  // Serial.println(ssid);

  /*Initializing the WiFi mode and connection*/
  WiFi.mode(WIFI_STA);//WiFi mode.
  WiFi.begin(ssid, password);//WiFi connection.

  /*Initializing the WiFi TCP/IP connection*/
  wifiMulti.addAP(ssid, password);
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  /*If the connection is succesful we print that the WiFi is connected and it's ip address, otherwise, we try again to make the connection*/
  // Serial.println("Connecting Wifi ");
  for (int loops = 10; loops > 0; loops--) {
    if (wifiMulti.run() == WL_CONNECTED) {
      //  Serial.println("");
      //  Serial.print("WiFi connected ");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      break;
    }
    else {
      //   Serial.println(loops);
      delay(1000);
    }
  }

  /*If the TCP/IP connection fails, we restart the ESP module and try again*/
  if (wifiMulti.run() != WL_CONNECTED) {
    //Serial.println("WiFi connect failed");
    delay(1000);
    ESP.restart();
  }

  //start UART and the server
  server.begin();//Server.
  server.setNoDelay(true);//UART.

  //Serial.print("Ready! Use 'telnet ");
  //Serial.print(WiFi.localIP());
  //Serial.println(" 80' to connect");

  /*We block the setup function until the WiFi get*/
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  //Serial.println("");
  //Serial.println("WiFi connected");
  // Print the IP address
  //Serial.println(WiFi.localIP());

  /*Begin the udp conection at the indicated port*/
  udpDevice.begin(localUdpPort);
}

/*This is the task that is going to receive the button pulsation bytes and write them again but to the high level TCP/IP client*/
void networkTask() {
  uint8_t data; //Variable that is going to store the data.
  uint8_t packetSize = udpDevice.parsePacket(); //Variable that stores the received packet in the udp connection.

  /*If we have bytes in the reception buffer of the esp32, we read the data package*/
  if (packetSize) {
    data = udpDevice.read();//Reading the data package.

    /*Depending on the byte read we write the same data from the TCP server to the TCP client in the processing sketch*/
    switch (data)
    {
      case '1':
        // Serial.write(data);
        serverClients[0].write('1');
        break;
      case '2':
        //Serial.write(data);
        serverClients[0].write('2');
        break;
      case '3':
        // Serial.write(data);
        serverClients[0].write('3');
        break;
    }
  }
}

void loop() {
  networkTask();
  uint8_t i;
  if (wifiMulti.run() == WL_CONNECTED) {
    //check if there are any new clients
    if (server.hasClient()) {
      for (i = 0; i < MAX_SRV_CLIENTS; i++) {
        //find free/disconnected spot
        if (!serverClients[i] || !serverClients[i].connected()) {
          if (serverClients[i]) serverClients[i].stop();
          serverClients[i] = server.available();
          //if (!serverClients[i]) Serial.println("available broken");
          //Serial.print("New client: ");
          //Serial.print(i); Serial.print(' ');
          //Serial.println(serverClients[i].remoteIP());
          break;
        }
      }
      if (i >= MAX_SRV_CLIENTS) {
        //no free/disconnected spot so reject
        server.available().stop();
      }
    }
    //check UART for data
    if (Serial.available()) {
      size_t len = serverClients[i].available();
      uint8_t sbuf[len];
      Serial.readBytes(sbuf, len);

      //push UART data to all connected telnet clients
      for (i = 0; i < MAX_SRV_CLIENTS; i++) {
        if (serverClients[i] && serverClients[i].connected()) {
          serverClients[i].write(sbuf, len);
          delay(1);
        }
      }
    }
  }
  else {
    //Serial.println("WiFi not connected!");
    for (i = 0; i < MAX_SRV_CLIENTS; i++) {
      if (serverClients[i]) serverClients[i].stop();
    }
    delay(1000);
  }
}
