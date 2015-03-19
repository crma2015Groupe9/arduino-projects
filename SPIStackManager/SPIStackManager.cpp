#include "Arduino.h"
#include "SPIStackableDevice.h"

SPIStackManager::SPIStackManager(SPIStackableDevice* devices, byte numberOfDevices, SPIStackableDevice_slaveSelectHandler handler){
	_devices = devices;
	_selectedDevice = 0;
	_numberOfDevices = numberOfDevices;
	_active = false;
	_useHandler = true;
	_slaveSelectHandler = handler;
}

SPIStackManager::SPIStackManager(SPIStackableDevice* devices, byte numberOfDevices){
	_devices = devices;
	_selectedDevice = 0;
	_numberOfDevices = numberOfDevices;
	_active = false;
	_useHandler = false;
}

void SPIStackManager::init(){
	byte i;
	for(i=0;i<_numberOfDevices;i++){
		if(_useHandler){
			_devices[i].isUsingCustomSelectHandler() ? _devices[i].init() : _slaveSelectHandler(HIGH, _devices[i].getID(), _devices[i].getCsPin(), _devices[i].getMark());
		}
		else{
			_devices[i].init();
		}
	}
}

void SPIStackManager::start(){
	_active = true;
}

void SPIStackManager::select(byte deviceID){

}

void SPIStackManager::selectDeviceAtIndex(byte index){


	start();
	_devices[i];
}

void SPIStackManager::end(){
	if(_active){
		_devices[_selectedDevice]
		_active = false;
	}
}