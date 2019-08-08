#include <XBee.h>

#define debugSerial Serial
#define xbeeSerial Serial1

XBee xbee = XBee();

uint8_t payload[10] = {0x54, 0x65, 0x73, 0x74};

// SH + SL Address of receiving XBee
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x40ABCBC2);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

//Object to parse the AT command response.
AtCommandResponse atCommandResoponse = AtCommandResponse();
// At command
AtCommandRequest atCommand = AtCommandRequest("CH");

// Variables to receive packets
ZBRxResponse rx = ZBRxResponse();
ModemStatusResponse msr = ModemStatusResponse();

void setup() {
  debugSerial.begin(9600);
  xbeeSerial.begin(9600);
  while (!debugSerial);
  xbee.setSerial(xbeeSerial);
}

void loop() {
  if (debugSerial.available()) {
    uint8_t data = debugSerial.read();
    if (data == '1') xbee.send(zbTx);
    if (data == '2') xbee.send(atCommand);
  }

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
    } else if (apiID == AT_COMMAND_RESPONSE) {
      xbee.getResponse().getAtCommandResponse(atCommandResoponse);
      debugSerial.print(F("STATUS: "));
      debugSerial.println(atCommandResoponse.getStatus());
      debugSerial.print(F("CHANNEL: "));
      uint8_t *pdata = atCommandResoponse.getValue();
      debugSerial.println(pdata[0], HEX);
    } else if (apiID == ZB_RX_RESPONSE) {
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
}

