/*
  A simple tool for ESP32 for collecting RF-codes from 
  a 433.92 MHz Key Fob / remote for a diesel heater using
  a 433 MHz receiver supported by the RCSwitch.h library.
  In the test setup a Chinese receiver XLC-RF-5V was used.

  On a ESP32-C mini board i recomend using GPIO 4 while on
  a board like ESP32 DevKit C (Wroom) you can use GPIO 16.

  Remember that most 433MHz receivers are 5 volt and you
  MUST USE a voltage divider to pull down the voltage.
  A 10 kOhm resistor between the DATA pin on the receiver 
  and the GPIO pin, and a 20 or 22 kOhm between the GPIO 
  and GND. This will give about 3.33 to 3.44 volt on the GPIO.

  Use the Serial Monitor while the ESP32 is connected via USB.
  Follow the intructions and press the called out buttons 
  on your remote / Key Fob, and copy the list of received
  codes from the Serial Monitor.
*/


#include <RCSwitch.h>

#define RF_RX_PIN 4

RCSwitch receiver = RCSwitch();
int receivedNo = 0;
unsigned long lastReceivedValue = 0;
unsigned long receivedValue = 0;
unsigned long storedValue[] = {0, 0, 0, 0};
String callOut[] = {"ON", "OFF", "UP", "DOWN"};
String divider = "----------------";

void setup() {

  Serial.begin(115200);
  delay(1000);

  receiver.enableReceive(RF_RX_PIN);

  Serial.println("Listening for 433 MHz codes...");
  Serial.println(" \r\n \r\n");
  Serial.print("Press ");
  Serial.println(callOut[receivedNo]);
  Serial.println(divider);

}

void loop() {

  if (receiver.available()) {
    receivedValue = receiver.getReceivedValue();
    if (receivedValue != lastReceivedValue) {

      storedValue[receivedNo] = receivedValue;
      Serial.print("Code: ");
      Serial.println(receiver.getReceivedValue());
      Serial.print("Bits: ");
      Serial.println(receiver.getReceivedBitlength());
      Serial.print("Protocol: ");
      Serial.println(receiver.getReceivedProtocol());
      Serial.println(divider);
      Serial.println("OK");
      Serial.println(divider);

      lastReceivedValue = receivedValue;
      delay(200);

      if (receivedNo == 3) {
        receivedNo = 0;
        Serial.println("Received codes: ");
        for (int i=0; i<=3; i++) {
          Serial.print(callOut[i]);
          Serial.print(": ");
          Serial.println(storedValue[i]);    
          storedValue[i] = 0; 
        }
        Serial.println(divider);
        Serial.println("To start over: ");
      } else {
        receivedNo += 1;
      }
      if (storedValue[receivedNo] == 0) {
        Serial.print("Press ");
        Serial.println(callOut[receivedNo]);
        Serial.println(divider);
      } 
    }
    receiver.resetAvailable();
  }

}
