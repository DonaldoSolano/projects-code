uint8_t Buffer[] = {0x7E,0x00,0x10 ,0x10 ,0x01 ,0x00 ,0x7D ,0x33 ,0xA2 ,0x00 ,0x40 ,0x52 ,0xDA ,0xB5 ,0xFF ,0xFE ,0x00 ,0x00 ,0x48 ,0x69 ,0x6A};

uint8_t AI[] = {0x7E, 0x00, 0x04, 0x08, 0x01, 0x41, 0x49, 0x6C};

void setup() {
  Serial.begin(9600);
  //while (!Serial) {  }
  Serial1.begin(9600);
}

void loop() {
  uint8_t data;
  static uint8_t counter = 0;

  if (Serial.available() > 0) {
    data = Serial.read();

    if (data == 'a') {
      for (uint8_t i = 0; i < 8; i++) {
        Serial1.write(AI[i]);
      }
   }

    for (uint8_t i = 0; i < 21; i++) {
      Serial1.write(Buffer[i]);
      //Serial.write(Buffer[i]);
    }
  }
  
  if (Serial1.available() > 0) {
      Serial.write(Serial1.read());
  }

  if(Serial){
    Serial.print('$');
    Serial.print(counter);
    Serial.println();
    counter++;
    delay(1000);
  }
}

