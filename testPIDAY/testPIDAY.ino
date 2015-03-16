#include <Potar.h>
#include <PushButton.h>
#include <TimeManager.h>

#define redPin 3
#define greenPin 5
#define bluePin 6

PushButton redUp(7);
PushButton redDown(8);
PushButton greenUp(9);
PushButton greenDown(11);
PushButton blueUp(12);
PushButton blueDown(4);

double red, green, blue, changeSpeed, outRed, outGreen, outBlue;

TimeManager time;

Potar intensity(A5, 255);

double colorChange(double value, boolean up, boolean down){
  if(up){
    value += changeSpeed*(double)time.delta()/1000;
  }
  if(down){
    value -= changeSpeed*(double)time.delta()/1000;
  }
  if(value < 0){value = 0;}
  if(value > 255){value = 255;}
  
  return value;
}


void setup(){
  changeSpeed = 25;
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  
  time.init();
  
  redUp.init();
  redDown.init();
  greenUp.init();
  greenDown.init();
  blueUp.init();
  blueDown.init();
  
  intensity.init();
  
  red = 0;
  green = 0;
  blue = 0;
}

void loop(){
  time.loopStart();
  
  redUp.update();
  redDown.update();
  greenUp.update();
  greenDown.update();
  blueUp.update();
  blueDown.update();
  
  intensity.update();
  
  /*===============*/
  red = colorChange(red, redUp.isPressed(), redDown.isPressed());
  green = colorChange(green, greenUp.isPressed(), greenDown.isPressed());
  blue = colorChange(blue, blueUp.isPressed(), blueDown.isPressed());
  /*===============*/
  
  double dIntensity = (double)intensity.currentValue();
  
  outRed = red*dIntensity/255;
  outGreen = green*dIntensity/255;
  outBlue = blue*dIntensity/255;
  
  analogWrite(redPin, (byte)outRed);
  analogWrite(greenPin, (byte)outGreen);
  analogWrite(bluePin, (byte)outBlue);
  
  time.loopEnd();
}
