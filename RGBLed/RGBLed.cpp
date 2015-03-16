#include "Arduino.h"
#include "RGBLed.h"

RGBLed::RGBLed(byte redPin, byte greenPin, byte bluePin, colorChangeHandler handler){
	_redPin = redPin;
	_greenPin = greenPin;
	_bluePin = bluePin;
	_useHandler = true;
	_colorChangeHandler = handler;
}

RGBLed::RGBLed(byte redPin, byte greenPin, byte bluePin){
	_redPin = redPin;
	_greenPin = greenPin;
	_bluePin = bluePin;
	_useHandler = false;
}

RGBLed::RGBLed(colorChangeHandler handler){
	_redPin = 0;
	_greenPin = 0;
	_bluePin = 0;
	_useHandler = true;
	_colorChangeHandler = handler;
}

void RGBLed::init(byte red, byte green, byte blue){
	if (!_useHandler)
	{
		pinMode(_redPin, OUTPUT);
		pinMode(_greenPin, OUTPUT);
		pinMode(_bluePin, OUTPUT);
	}

	_red = red;
	_green = green;
	_blue = blue;

	changeColor(_red, _green, _blue);
}

void RGBLed::init(){
	init(0, 0, 0);
}

void RGBLed::changeColor(byte red, byte green, byte blue){
	_red = red;
	_green = green;
	_blue = blue;

	if (_useHandler)
	{
		_colorChangeHandler(_red, _green, _blue);
	}
	else{
		_defaultColorChangeHandler(_red, _green, _blue);
	}
}

void RGBLed::rgb(byte red, byte green, byte blue){
	changeColor(red, green, blue);
}

void RGBLed::r(byte red){
	changeColor(red, _green, _blue);
}

void RGBLed::g(byte green){
	changeColor(_red, green, _blue);
}

void RGBLed::b(byte blue){
	changeColor(_red, _green, blue);
}

void RGBLed::rg(byte red, byte green){
	changeColor(red, green, _blue);
}

void RGBLed::rb(byte red, byte blue){
	changeColor(red, _green, blue);
}

void RGBLed::gb(byte green, byte blue){
	changeColor(_red, green, blue);
}

void RGBLed::_defaultColorChangeHandler(byte red, byte green, byte blue){
	analogWrite(_redPin, red);
	analogWrite(_greenPin, green);
	analogWrite(_bluePin, blue);
}

byte RGBLed::getRed(){
	return _red;
}

byte RGBLed::getGreen(){
	return _green;
}

byte RGBLed::getBlue(){
	return _blue;
}