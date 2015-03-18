#ifndef SPIStackManager_h
#define SPIStackManager_h

#include "Arduino.h"
#include "SPIStackableDevice.h"

class SPIStackManager
{
	public:
		SPIStackManager(SPIStackableDevice* devices, byte numberOfDevices, SPIStackableDevice_slaveSelectHandler handler);
		SPIStackManager(SPIStackableDevice* devices, byte numberOfDevices);
		void init();

		void start();
		void select(byte deviceID);
		void selectDeviceAtIndex(byte index);
		void end();
	private:
		SPIStackableDevice *_devices;
		byte _selectedDevice;
		byte _numberOfDevices;
		boolean _active;
		boolean _useHandler;
		SPIStackableDevice_slaveSelectHandler _slaveSelectHandler;
};

#endif