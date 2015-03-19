#include <SPI.h>
#include "Arduino.h"
#include "SPIStackManager.h"

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
		if(_useDeviceSelectHandler(i)){
			_devices[i].init();
		}
		else{
			pinMode(_devices[i].getCsPin(), OUTPUT);
			_slaveSelectHandler(HIGH, _devices[i].getID(), _devices[i].getCsPin(), _devices[i].getMark());
			
			_devices[i].SPIStackManager_setState(HIGH);
		}
	}

	SPI.begin();
}

boolean SPIStackManager::_useDeviceSelectHandler(byte deviceIndex){
	return !(_useHandler && !(_devices[deviceIndex].isUsingCustomSelectHandler()));
}

void SPIStackManager::start(){
	_active = true;
}

boolean SPIStackManager::select(byte deviceID){
	return selectDeviceAtIndex(_getIndexForDeviceID(deviceID));
}

boolean SPIStackManager::unselect(byte deviceID){
	return unselectDeviceAtIndex(_getIndexForDeviceID(deviceID));
}

boolean SPIStackManager::unselectDeviceAtIndex(byte index){
	if (index >= _numberOfDevices){return false;}

	if(_active){
		if (_useDeviceSelectHandler(index))
		{
			_devices[index].unselect();
		}
		else{
			_slaveSelectHandler(HIGH, _devices[index].getID(), _devices[index].getCsPin(), _devices[index].getMark());
			_devices[index].SPIStackManager_setState(HIGH);
		}
	}

	return true;
}

byte SPIStackManager::_getIndexForDeviceID(byte deviceID){
	byte i;
	for(i=0;i<_numberOfDevices;i++){
		if (_devices[i].getID() == deviceID)
		{
			return i;
		}
	}

	return _numberOfDevices;
}

void SPIStackManager::unselectCurrentDevice(){
	unselectDeviceAtIndex(_selectedDevice);
}

boolean SPIStackManager::selectDeviceAtIndex(byte index){
	if (index >= _numberOfDevices){return false;}

	_active ? unselectCurrentDevice() : start();

	if (_useDeviceSelectHandler(index))
	{
		_devices[index].select();
	}
	else{
		_slaveSelectHandler(LOW, _devices[index].getID(), _devices[index].getCsPin(), _devices[index].getMark());
		_devices[index].SPIStackManager_setState(LOW);
	}

	_selectedDevice = index;

	return true;
}

void SPIStackManager::end(){
	if(_active){
		unselectCurrentDevice();
		_active = false;
	}
}