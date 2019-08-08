#include <XBee.h>

#define debugSerial Serial
#define xbeeSerial Serial1

unsigned long previousMillis = 0;        // will store last time photoresistor was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)



uint8_t lightSensorOne = A0, lightSensorTwo = A1;
uint16_t lecSensorOne, lecSensorTwo;
unsigned char motorState = 0;
unsigned char motorPower = 128;

XBee xbee = XBee();

ZBTxStatusResponse txStatus = ZBTxStatusResponse();



//Variables to send packets
uint8_t payload[2];

// SH + SL Address of receiving XBee
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x40AF0DD8);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));



// Variables to receive packets
ZBRxResponse rx = ZBRxResponse();
ModemStatusResponse msr = ModemStatusResponse();

void setup() {
  //reflex
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(8, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  //  pinMode(lightSensorOne, INPUT);
  //  pinMode(lightSensorTwo, INPUT);
  //

  debugSerial.begin(9600);
  xbeeSerial.begin(9600);

  // put your setup code here, to run once:

}

void loop() {
  //---------------------------------------------------------------------
  lecSensorOne = map(analogRead(lightSensorOne), 0, 1023, 0, 10);
  payload[0] = lecSensorOne;
  //debugSerial.print(lecSensorOne);
  //delay(500);

  lecSensorTwo = map(analogRead(lightSensorTwo), 0, 1023, 0, 10);
  payload[1] = lecSensorTwo;
  //debugSerial.print(lecSensorTwo);
  //delay(500);

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    xbee.send(zbTx);
  }




  //---------------------------------------------------------------------
  xbee.readPacket();
  if (xbee.getResponse().isAvailable()) { // Returns true if the response has been successfully parsed and is complete and ready for use
    uint8_t apiID = xbee.getResponse().getApiId();
    if (apiID == ZB_TX_STATUS_RESPONSE) {
      xbee.getResponse().getZBTxStatusResponse(txStatus);
      debugSerial.print(F("REMOTE ADDRESS: "));
      debugSerial.println(txStatus.getRemoteAddress(), HEX);
      debugSerial.print(F("RETRY COUNT: "));
      debugSerial.println(txStatus.getTxRetryCount());
      debugSerial.print(F("DELIVERY STATUS: "));
      debugSerial.println(txStatus.getDeliveryStatus(), HEX);
      debugSerial.print(F("DISCOVERY STATUS: "));
      debugSerial.println(txStatus.getDiscoveryStatus(), HEX);
    }

    else if (apiID == ZB_RX_RESPONSE) {
      // now fill our zb rx class
      xbee.getResponse().getZBRxResponse(rx);

      debugSerial.print(F("RX FROM: "));
      XBeeAddress64& addressFrom = rx.getRemoteAddress64();
      debugSerial.print(addressFrom.getMsb(), HEX);
      debugSerial.println(addressFrom.getLsb(), HEX);
      debugSerial.print(F("RX FROM: "));
      debugSerial.println(rx.getRemoteAddress16());

      if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED) {
        // the sender got an ACK
        debugSerial.println(F("SENDER GOT AN ACK"));
        for (uint8_t i = 0; i < rx.getDataLength(); i++) {
          debugSerial.write(rx.getData(i));
        }
        switch (rx.getData(1)) {
          case '1':
            motorPower = 50;
            break;
          case '2':
            motorPower = 100;
            break;
          case '3':
            motorPower = 150;
            break;
          case '4':
            motorPower = 200;
            break;
          case '5':
            motorPower = 255;
            break;
        }
        switch (rx.getData(0)) {
          case 'F':
            analogWrite(5, motorPower);
            analogWrite(6, motorPower);
            digitalWrite(4, 1);
            digitalWrite(7, 1);
            //Serial.println(F("Adelante"));
            break;

          case 'B':
            analogWrite(5, motorPower);
            analogWrite(6, motorPower);
            digitalWrite(4, 0);
            digitalWrite(7, 0);
            //Serial.println(F("Atras"));
            break;

          case 'R':
            analogWrite(5, motorPower);
            analogWrite(6, 0);
            digitalWrite(4, 1);
            digitalWrite(7, 0);
            //Serial.println(F("Derecha"));
            break;

          case 'L':
            analogWrite(5, 0);
            analogWrite(6, motorPower);
            digitalWrite(4, 0);
            digitalWrite(7, 1);
            //Serial.println(F("Izquierda"));
            break;
          default:
            analogWrite(5, 0);
            analogWrite(6, 0);
            digitalWrite(4, 0);
            digitalWrite(7, 0);
            //Serial.println(F("Detenido"));

            break;

        }


        debugSerial.println();
      } else {
        // we got it (obviously) but sender didn't get an ACK
        debugSerial.println(F("SENDER DIDN'T GET AN ACK"));
      }

    } else if (apiID == MODEM_STATUS_RESPONSE) {
      xbee.getResponse().getModemStatusResponse(msr);
      // the local XBee sends this response on certain events, like association/dissociation
      if (msr.getStatus() == ASSOCIATED) {
        // yay this is great.  flash led
        debugSerial.println(F("ASSOCIATED"));

      } else if (msr.getStatus() == DISASSOCIATED) {
        debugSerial.println(F("DISASSOCIATED"));
      } else {
        // another status
        debugSerial.println(F("another status"));
      }
    }
    else {
      debugSerial.print("API ID: ");
      debugSerial.println(apiID);
    }
  }
  else if (xbee.getResponse().isError()) { // returns true if the response contains errors
    // There is an error on the frame
    debugSerial.print("Error code: ");
    debugSerial.println(xbee.getResponse().getErrorCode());
  }
  //--------------------------------------------------------------------------------------------------------------------------------------------



}

// put your main code here, to run repeatedly:

