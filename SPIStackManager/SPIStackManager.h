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
		boolean select(byte deviceID);
		boolean selectDeviceAtIndex(byte index);
		boolean unselect(byte deviceID);
		boolean unselectDeviceAtIndex(byte index);
		void unselectCurrentDevice();
		void end();
	private:
		SPIStackableDevice *_devices;
		byte _selectedDevice;
		byte _numberOfDevices;
		boolean _active;
		boolean _useHandler;
		SPIStackableDevice_slaveSelectHandler _slaveSelectHandler;

		boolean _useDeviceSelectHandler(byte deviceIndex);
		byte _getIndexForDeviceID(byte deviceID);
};

#endif