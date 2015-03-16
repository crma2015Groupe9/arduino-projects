#include "Arduino.h"
#include "PushButton.h"

PushButton::PushButton(byte pin){
	_pin = pin;
	_usePin = true;
}

PushButton::PushButton(){
	_pin = 0;
	_usePin = false;
}

void PushButton::init(boolean defaultValue){
	_defaultValue = defaultValue;
	if (_usePin){pinMode(_pin, INPUT);}
	_pinValue = _usePin ? digitalRead(_pin) : _defaultValue;
	_previousPinValue = _pinValue;
	_waitForPush = !isPressed();
	_clickDown = false;
	_clickUp = false;
}

void PushButton::init(){
	init(LOW);
}

void PushButton::update(boolean digitalValue){
	_previousPinValue = _pinValue;
	_pinValue = _usePin ? digitalRead(_pin) : digitalValue;

	_clickDown = false;
	_clickUp = false;

	if (isPressed() && _waitForPush)
	{
		_waitForPush = false;
		_clickDown = true;
	}
	else if (!isPressed() && !_waitForPush)
	{
		_waitForPush = true;
		_clickUp = true;
	}
}

void PushButton::update(){
	update(_defaultValue);
}

boolean PushButton::stateChanged(){
	return _pinValue != _previousPinValue;
}

boolean PushButton::isPressed(){
	return _pinValue != _defaultValue;
}

boolean PushButton::clickDown(){
	return _clickDown;
}

boolean PushButton::clickUp(){
	return _clickUp;
}