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

void RGBLed::init(byte red, byte green, byte blue, byte intensity){
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
	_intensity = intensity;

	changeColor(_red, _green, _blue);
}

void RGBLed::init(byte red, byte green, byte blue){
	init(red, green, blue, 255);
}

void RGBLed::init(){
	init(0, 0, 0);
}

void RGBLed::changeColor(byte red, byte green, byte blue, byte intensity){
	_intensity = intensity;

	changeColor(red, green, blue);
}

void RGBLed::changeColor(byte red, byte green, byte blue){
	_red = red;
	_green = green;
	_blue = blue;

	_colorChange(_red, _green, _blue);
}

void RGBLed::_colorChange(byte red, byte green, byte blue){
	red = _applyIntensity(red);
	green = _applyIntensity(green);
	blue = _applyIntensity(blue);

	if (_useHandler)
	{
		_on ? _colorChangeHandler(red, green, blue, _redPin, _greenPin, _bluePin, _mark) : _colorChangeHandler(0, 0, 0, _redPin, _greenPin, _bluePin, _mark);
	}
	else{
		_on ? _defaultColorChangeHandler(red, green, blue) : _defaultColorChangeHandler(0, 0, 0);
	}
}

byte RGBLed::_applyIntensity(byte value){
	return (byte)((unsigned long)value*(unsigned long)intensity/255);
}

void RGBLed::rgbi(byte red, byte green, byte blue, byte intensity){
	changeColor(red, green, blue, intensity);
}

void RGBLed::rgb(byte red, byte green, byte blue){
	changeColor(red, green, blue, _intensity);
}

void RGBLed::i(byte intensity){
	changeColor(_red, _green, _blue, intensity);
}

void RGBLed::ri(byte red, byte intensity){
	changeColor(red, _green, _blue, intensity);
}

void RGBLed::r(byte red){
	ri(red, _intensity);
}

void RGBLed::gi(byte green, byte intensity){
	changeColor(_red, green, _blue, intensity);
}

void RGBLed::g(byte green){
	gi(green, _intensity);
}

void RGBLed::bi(byte blue, byte intensity){
	changeColor(_red, _green, blue, intensity);
}

void RGBLed::b(byte blue){
	bi(blue, _intensity);
}

void RGBLed::rgi(byte red, byte green, byte intensity){
	changeColor(red, green, _blue, intensity);
}

void RGBLed::rg(byte red, byte green){
	rgi(red, green, _intensity);
}

void RGBLed::rbi(byte red, byte blue, byte intensity){
	changeColor(red, _green, blue, intensity);
}

void RGBLed::rb(byte red, byte blue){
	rbi(red, blue, _intensity);
}

void RGBLed::gbi(byte green, byte blue, byte intensity){
	changeColor(_red, green, blue, intensity);
}

void RGBLed::gb(byte green, byte blue){
	gbi(green, blue, _intensity);
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

byte RGBLed::getIntensity(){
	return _intensity;
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

void RGBLed::lighter(byte value){
	i(_calculNewValue(getIntensity(), value, 0));
}
void RGBLed::lighter(){
	lighter(1);
}
void RGBLed::darker(byte value){
	i(_calculNewValue(getIntensity(), 0, value));
}
void RGBLed::darker(){
	darker(1);
}