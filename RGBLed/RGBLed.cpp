#include "Arduino.h"
#include "RGBLed.h"

RGBLed::RGBLed(byte redPin, byte greenPin, byte bluePin, colorChangeHandler handler, byte mark){
	_redPin = redPin;
	_greenPin = greenPin;
	_bluePin = bluePin;
	_useHandler = true;
	_colorChangeHandler = handler;
	_mark = mark;
}

RGBLed::RGBLed(byte redPin, byte greenPin, byte bluePin, colorChangeHandler handler){
	_redPin = redPin;
	_greenPin = greenPin;
	_bluePin = bluePin;
	_useHandler = true;
	_colorChangeHandler = handler;
	_mark = 0;
}

RGBLed::RGBLed(byte redPin, byte greenPin, byte bluePin){
	_mark = 0;
	_redPin = redPin;
	_greenPin = greenPin;
	_bluePin = bluePin;
	_useHandler = false;
}

RGBLed::RGBLed(colorChangeHandler handler, byte mark){
	_mark = mark;
	_redPin = 0;
	_greenPin = 0;
	_bluePin = 0;
	_useHandler = true;
	_colorChangeHandler = handler;
}

byte RGBLed::mark(){
	return _mark;
}

void RGBLed::init(byte red, byte green, byte blue){
	_on = true;

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

	_colorChange(_red, _green, _blue);
}

void RGBLed::_colorChange(byte red, byte green, byte blue){
	if (_useHandler)
	{
		_on ? _colorChangeHandler(red, green, blue, _redPin, _greenPin, _bluePin, _mark) : _colorChangeHandler(0, 0, 0, _redPin, _greenPin, _bluePin, _mark);
	}
	else{
		_on ? _defaultColorChangeHandler(red, green, blue) : _defaultColorChangeHandler(0, 0, 0);
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

void RGBLed::off(){
	_on = false;
	_colorChange(_red, _green, _blue);
}

void RGBLed::on(){
	_on = true;
	_colorChange(_red, _green, _blue);
}

void RGBLed::toggle(){
	_on ? off() : on();
}

byte RGBLed::_calculNewValue(byte baseValue, byte addValue, byte lessValue){
	int newValue;
	newValue = (int)baseValue+(int)addValue-(int)lessValue;
	if(newValue > 255){
		newValue = 255;
	}
	else if(newValue < 0){
		newValue = 0;
	}

	return (byte)newValue;
}

void RGBLed::moreRed(byte value){
	r(_calculNewValue(getRed(), value, 0));
}
void RGBLed::moreRed(){
	moreRed(1);
}
void RGBLed::lessRed(byte value){
	r(_calculNewValue(getRed(), 0, value));
}
void RGBLed::lessRed(){
	lessRed(1);
}

void RGBLed::moreGreen(byte value){
	g(_calculNewValue(getGreen(), value, 0));
}
void RGBLed::moreGreen(){
	moreGreen(1);
}
void RGBLed::lessGreen(byte value){
	g(_calculNewValue(getGreen(), 0, value));
}
void RGBLed::lessGreen(){
	lessGreen(1);
}

void RGBLed::moreBlue(byte value){
	b(_calculNewValue(getBlue(), value, 0));
}
void RGBLed::moreBlue(){
	moreBlue(1);
}
void RGBLed::lessBlue(byte value){
	b(_calculNewValue(getBlue(), 0, value));
}
void RGBLed::lessBlue(){
	lessBlue(1);
}