#include <SPI.h>

#include <SPIStackableDevice.h>
#include <SPIStackManager.h>
#include <SPIDigitalPot.h>

#include <TimeManager.h>
#include <Tween.h>

#include <PushButton.h>
#include <RGBLed.h>

/*---------------------*/

#define NUMBER_OF_LEDS 4
#define NUMBER_OF_SPI_DEVICES 2

#define digitalPotOne 4
#define digitalPotTwo 10

/*----------------------*/
/*SPI Devices Management*/
/*----------------------*/

SPIStackableDevice SPIDevices[NUMBER_OF_SPI_DEVICES] = {
  SPIStackableDevice(digitalPotOne),
  SPIStackableDevice(digitalPotTwo)
};

SPIStackManager SPIStack(SPIDevices, NUMBER_OF_SPI_DEVICES); 

/*----------*/
void digitalPotSelectMethod(boolean state, byte csPin, byte mark){
  //Le state correspond a l'etat qui doit etre appliqué : HIGH pour déselectionner et LOW pour selectionner
  state ? SPIStack.unselect(csPin) : SPIStack.select(csPin);
}

SPIDigitalPot digitalPot[] = {
  SPIDigitalPot(digitalPotOne, digitalPotSelectMethod),
  SPIDigitalPot(digitalPotTwo, digitalPotSelectMethod)
};

/*---------------*/

TimeManager time;
Tween intensityTween, loaderTween;

/*---------------*/

void colorChangeMethod(byte red, byte green, byte blue, byte redChannel, byte greenChannel, byte blueChannel, byte potID){
  digitalPot[potID].write(redChannel, red);
  digitalPot[potID].write(greenChannel, green);
  digitalPot[potID].write(blueChannel, blue);
  
  SPIStack.end();
}

RGBLed led[NUMBER_OF_LEDS] = {
  RGBLed(1, 3, 2, colorChangeMethod, 0),
  RGBLed(4, 6, 5, colorChangeMethod, 0),
  RGBLed(1, 3, 2, colorChangeMethod, 1),
  RGBLed(4, 6, 5, colorChangeMethod, 1)
};

PushButton loadButton(8);

byte red, green, blue;

/*-----------------*/

void setup() {
  byte i;

  Serial.begin(9600);
  
  SPIStack.init();
  
  time.init();
  intensityTween.transition(230, 255, 800);
  loaderTween.transition(-5, 8, 800);
  intensityTween.pause();
  loaderTween.pause();
  
  red = 255; green = 0; blue = 0;
  for(i=0;i<NUMBER_OF_LEDS;i++){
    led[i].init();
  }
  
  loadButton.init();
}

void loop() {
  int currentLedIndex, intensity, intensity2, i, diff;
  
  time.loopStart();
  intensityTween.update(time.delta());
  loaderTween.update(time.delta());
    
  loadButton.update(); 
  
  /*=============================*/
    
  intensity = (int)intensityTween.linearValue();
  currentLedIndex = (int)loaderTween.easeOutQuadValue();
    
  for(i=0;i<NUMBER_OF_LEDS;i++){
    if(i == currentLedIndex){
      led[i].rgbi(red, green, blue, (byte)intensity);
    }
    else{
      diff = currentLedIndex > i ? currentLedIndex-i : i-currentLedIndex;
        
      intensity2 = intensity-(diff*diff*12);
      intensity2 = intensity2 < 0 ? 0 : intensity2;
      intensity2 = intensity2 > 255 ? 255 : intensity2;
      led[i].rgbi(red, green, blue, (byte)intensity2);
    }
  }
    
  if(loadButton.clickUp()){
    if(intensityTween.isEnded()){
      intensityTween.replay();
      loaderTween.replay();
    }
    else{
      intensityTween.play();
      loaderTween.play();
    }
  }
  
  /*==============================*/
  
  time.loopEnd();
}