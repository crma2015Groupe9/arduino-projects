  #include <RGBLed.h>
#include <PushButton.h>
#include <SPI.h>

int digitalPotentiometerPins[] = {10};
byte currentColor;

void colorChangeMethod(byte red, byte green, byte blue, byte redChannel, byte greenChannel, byte blueChannel, byte potID){
  digitalWrite(digitalPotentiometerPins[potID],LOW);
  SPI.transfer(redChannel);
  SPI.transfer(red);
  digitalWrite(digitalPotentiometerPins[potID],HIGH);
  digitalWrite(digitalPotentiometerPins[potID],LOW);
  SPI.transfer(greenChannel);
  SPI.transfer(green);
  digitalWrite(digitalPotentiometerPins[potID],HIGH);
  digitalWrite(digitalPotentiometerPins[potID],LOW);
  SPI.transfer(blueChannel);
  SPI.transfer(blue);
  digitalWrite(digitalPotentiometerPins[potID],HIGH); 
}

RGBLed lights[] = {
  RGBLed(5, 1, 3, colorChangeMethod, 0)
};

PushButton switchButton(2);

void setup() {
  Serial.begin(9600);
  
  currentColor = 0;
    
  pinMode (digitalPotentiometerPins[0], OUTPUT);
  SPI.begin();
  
  switchButton.init();
  lights[0].init();
}

void loop() {
  switchButton.update();
  
  if(switchButton.clickUp()){
    currentColor++;
    currentColor = currentColor == 8 ? 0 : currentColor;
  }
  
  switch(currentColor){
    case 1:
      lights[0].rgb(255, 0, 0);
    break;
    
    case 2:
      lights[0].rgb(0, 255, 0);
    break;
    
    case 3:
      lights[0].rgb(0, 0, 255);
    break;
    
    case 4:
      lights[0].rgb(230, 150, 0);
    break;
    
    case 5:
      lights[0].rgb(220, 0, 168);
    break;
    
    case 6:
      lights[0].rgb(138, 220, 0);
    break;
    
    case 7:
      lights[0].rgb(0, 220, 200);
    break;
    
    default:
      lights[0].rgb(0, 0, 0);
    break;
  }
}