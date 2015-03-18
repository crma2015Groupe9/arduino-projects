#include "Arduino.h"
#include "SPIStackableDevice.h"

SPIStackableDevice::SPIStackableDevice(byte id, byte csPin, byte mark, SPIStackableDevice_slaveSelectHandler handler){
	_id = id;
	_csPin = csPin;
	_mark = mark;
	_useHandler = true;
	_slaveSelectHandler = handler;
}

SPIStackableDevice::SPIStackableDevice(byte id, byte csPin, SPIStackableDevice_slaveSelectHandler handler){
	_id = id;
	_csPin = csPin;
	_mark = 0;
	_useHandler = true;
	_slaveSelectHandler = handler;
}

SPIStackableDevice::SPIStackableDevice(byte csPinAndID, SPIStackableDevice_slaveSelectHandler handler){
	_id = csPinAndID;
	_csPin = csPinAndID;
	_mark = 0;
	_useHandler = true;
	_slaveSelectHandler = handler;
}

SPIStackableDevice::SPIStackableDevice(byte id, byte csPin, byte mark){
	_id = id;
	_csPin = csPin;
	_mark = mark;
	_useHandler = false;
}

SPIStackableDevice::SPIStackableDevice(byte id, byte csPin){
	_id = id;
	_csPin = csPin;
	_mark = 0;
	_useHandler = false;
}

SPIStackableDevice::SPIStackableDevice(byte csPinAndID){
	_id = csPinAndID;
	_csPin = csPinAndID;
	_mark = 0;
	_useHandler = false;
}

void SPIStackableDevice::init(){
	pinMode(_csPin, OUTPUT);

	_state = HIGH;

	_useHandler ? _slaveSelectHandler(HIGH, _id, _csPin, _mark) : digitalWrite(_csPin, HIGH);
}

void SPIStackableDevice::select(){
	_state = LOW;

	_useHandler ? _slaveSelectHandler(LOW, _id, _csPin, _mark) : digitalWrite(_csPin, LOW);
}

void SPIStackableDevice::unselect(){
	_state = HIGH;

	_useHandler ? _slaveSelectHandler(HIGH, _id, _csPin, _mark) : digitalWrite(_csPin, HIGH);
}

byte SPIStackableDevice::getID(){
	return _id;
}

byte SPIStackableDevice::getCsPin(){
	return _csPin;
}

byte SPIStackableDevice::getMark(){
	return _mark;
}

void SPIStackableDevice::SPIStackManager_setState(boolean state){
	_state = state;
}

boolean SPIStackableDevice::isSelected(){
	return !_state;
}

boolean SPIStackableDevice::isUsingCustomSelectHandler(){
	return _useHandler;
}