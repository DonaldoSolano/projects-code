#include <XBee.h>
//Joystick 1
uint8_t x1 = A2;
uint8_t y1 = A1;

//Joystick 2
uint16_t x2 = A5;
uint16_t y2 = A4;


#define debugSerial Serial
#define xbeeSerial Serial1

uint16_t lecx1, lecy1, lecy2, lecx2;
XBee xbee = XBee();

uint8_t payload[2];

// SH + SL Address of receiving XBee
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x40ABCBC2);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

void setup() {
  debugSerial.begin(9600);
  xbeeSerial.begin(9600);
  //while (!debugSerial);
  xbee.setSerial(xbeeSerial);
}

void loop() {
  lecy1 = map(analogRead(y1), 0, 1023, 0, 10);
  //debugSerial.print(lecy1);
  //delay(500);

  lecx1 = map(analogRead(x1), 0, 1023, 0, 10);
  //debugSerial.print(lecx1);
  //delay(500);


  lecy2 = map(analogRead(y2), 0, 1023, 0, 10);
  //debugSerial.print(lecy2);
  //delay(500);

  lecx2 = map(analogRead(x2), 0, 1023, 0, 10);
  //debugSerial.print(lecx2);
  // delay(500);
  //debugSerial.println();



  switch (lecy1) {
    case 6 ... 10:
      payload[0] = 'F';
      break;

    case 0 ... 3:
      payload[0] = 'B';
      break;

    case 4:
      payload[0] = 0;
      break;
  }
  switch (lecx1) {
    case 6 ... 10:
      payload[0] = 'R';
      break;

    case 0 ... 4:
      payload[0] = 'L';
      break;

  }
  switch (lecy2) {
    case 5:
      payload[1] = '2';
      break;

    case 6 ... 7:
      payload[1] = '3';
      break;

    case 8 ... 9:
      payload[1] = '4';
      break;

    case 10:
      payload[1] = '5';
      break;

    default:
      payload[1] = '0';
      break;
  }


  xbee.send(zbTx);




}

