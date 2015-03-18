#include "Arduino.h"
#include "SPIStackableDevice.h"

SPIStackManager::SPIStackManager(SPIStackableDevice* devices, byte numberOfDevices, SPIStackableDevice_slaveSelectHandler handler){
	_id = id;
	_csPin = csPin;
	_mark = mark;
	_useHandler = true;
	_slaveSelectHandler = handler;
}

SPIStackManager::SPIStackManager(SPIStackableDevice* devices, byte numberOfDevices){
	
}

void SPIStackManager::init(){
	pinMode(_csPin, OUTPUT);

	_state = HIGH;

	_useHandler ? _slaveSelectHandler(HIGH, _id, _csPin, _mark) : digitalWrite(_csPin, HIGH);
}