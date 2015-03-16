#include "Arduino.h"
#include "SDCardModule.h"

SDCardModule::SDCardModule(byte csPin){
	_csPin = csPin;
	_usePin = true;
}

void SDCardModule::init(){
}

/*
#define SDCardReaderPin 10
#define fileName "lights.txt"

boolean sdCardOk, fileExists;
File lightFile;

void setup(){
  Serial.begin(9600);
  while (!Serial) {;}
  
  pinMode(SDCardReaderPin, OUTPUT);
  
  digitalWrite(SDCardReaderPin, HIGH);
  
  sdCardOk = SD.begin(SDCardReaderPin);
  
  digitalWrite(SDCardReaderPin, HIGH);
  
  fileExists = SD.exists(fileName);
  
  if(!fileExists){
    lightFile = SD.open(fileName, FILE_WRITE);
    lightFile.print("magic carpet ride");
    lightFile.close();
  }
  
  lightFile = SD.open(fileName);
}

void loop(){
  char letter;
  
  if(sdCardOk){
    while(lightFile.available()){
      letter = lightFile.read();
      lightFile.position() == lightFile.size() ? Serial.println(letter) : Serial.print(letter);
    }
    
    Serial.println("---------");
    lightFile.seek(0);
  }
  
  delay(2500);
}
*/