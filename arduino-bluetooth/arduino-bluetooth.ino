/*********************************************************************
This is an example for our nRF8001 Bluetooth Low Energy Breakout

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1697

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Kevin Townsend/KTOWN  for Adafruit Industries.
MIT license, check LICENSE for more information
All text above, and the splash screen below must be included in any redistribution
*********************************************************************/

// This version uses the internal data queing so you can treat it like Serial (kinda)!

#include <SPI.h>
#include "Adafruit_BLE_UART.h"
#include <ArduinoJson.h>

// Connect CLK/MISO/MOSI to hardware SPI
// e.g. On UNO & compatible: CLK = 13, MISO = 12, MOSI = 11
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2     // This should be an interrupt pin, on Uno thats #2 or #3
#define ADAFRUITBLE_RST 9

Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);

// DynamicJsonBuffer jsonBuffer;
boolean getJsonString = false;
String jsonString = "";


/**************************************************************************/
/*!
    Configure the Arduino and start advertising with the radio
*/
/**************************************************************************/
void setup(void)
{
    Serial.begin(9600);
    while(!Serial); // Leonardo/Micro should wait for serial init
    Serial.println(F("Adafruit Bluefruit Low Energy nRF8001 Print echo demo"));

    // BTLEserial.setDeviceName("NEWNAME"); /* 7 characters max! */

    BTLEserial.begin();
}

/**************************************************************************/
/*!
    Constantly checks for new events on the nRF8001
*/
/**************************************************************************/
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;

void loop()
{
    // Tell the nRF8001 to do whatever it should be working on.
    BTLEserial.pollACI();

    // Ask what is our current status
    aci_evt_opcode_t status = BTLEserial.getState();
    // If the status changed....
    if (status != laststatus) {
        // print it out!
        if (status == ACI_EVT_DEVICE_STARTED) {
            Serial.println(F("* Advertising started"));
        }
        if (status == ACI_EVT_CONNECTED) {
            Serial.println(F("* Connected!"));
        }
        if (status == ACI_EVT_DISCONNECTED) {
            Serial.println(F("* Disconnected or advertising timed out"));
        }
        // OK set the last status change to this one
        laststatus = status;
    }

    if (status == ACI_EVT_CONNECTED) {
        // Lets see if there's any data for us!
        if (BTLEserial.available()) {
            Serial.print("* "); Serial.print(BTLEserial.available()); Serial.println(F(" bytes available from BTLE"));
        }
        String data = "";
        // OK while we still have something to read, get a character and print it out
        while (BTLEserial.available()) {
            char c = BTLEserial.read();
            // Serial.print(c);
            data += c;
        }

        if (data == "END") {
            getJsonString = false;
            // Serial.print(jsonString);

            int jsonLength = jsonString.length();
            jsonString += '\0';
            jsonLength = jsonString.length();
            char json[jsonLength];
            jsonString.toCharArray(json, jsonLength);
            
            parseJson(json, jsonLength);
            test();

            // const char* test = root["BlogName"].asString();
            // Serial.print(test);
            jsonString = "";
        }

        if (getJsonString) {
            jsonString += data;
        }

        if (data == "START") {
            getJsonString = true;
        }


        // Next up, see if we have any data to get from the Serial console

        if (Serial.available()) {
            // Read a line from Serial
            Serial.setTimeout(100); // 100 millisecond timeout
            String s = Serial.readString();

            // We need to convert the line to bytes, no more than 20 at this time
            uint8_t sendbuffer[20];
            s.getBytes(sendbuffer, 20);
            char sendbuffersize = min(20, s.length());

            Serial.print(F("\n* Sending -> \"")); Serial.print((char *)sendbuffer); Serial.println("\"");

            // write the data
            BTLEserial.write(sendbuffer, sendbuffersize);
        }
    }
}

void parseJson(char* json, int jsonLength)
{
    const int BUFFER_SIZE = JSON_OBJECT_SIZE(2);
    StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);

    if (!root.success())
    {
        // Parsing fail
        Serial.println("fail");
    }
    else {
        Serial.println("success");
    }
}

void test()
{
    const int BUFFER_SIZE = JSON_OBJECT_SIZE(2);
    StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;
    // StaticJsonBuffer<200> jsonBuffer;

    char json[] = "{\"BlogName\":3,\"BlogDomain\":4}";

    JsonObject& root = jsonBuffer.parseObject(json);

    if (!root.success()) {
        Serial.println("parseObject() failed");
        return;
    }
    else {
        Serial.println("parseObject() success");
    }
}
