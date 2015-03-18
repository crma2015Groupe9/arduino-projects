#ifndef SPIStackableDevice_h
#define SPIStackableDevice_h

#include "Arduino.h"

class SPIStackableDevice;
typedef void (*SPIStackableDevice_slaveSelectHandler)(boolean, byte, byte, byte);
//state, id, cspin, mark

class SPIStackableDevice
{
	public:
		SPIStackableDevice(byte id, byte csPin, byte mark, SPIStackableDevice_slaveSelectHandler handler);
		SPIStackableDevice(byte id, byte csPin, SPIStackableDevice_slaveSelectHandler handler);
		SPIStackableDevice(byte csPinAndID, SPIStackableDevice_slaveSelectHandler handler);

		SPIStackableDevice(byte id, byte csPin, byte mark);
		SPIStackableDevice(byte id, byte csPin);
		SPIStackableDevice(byte csPinAndID);

		void init();

		void select();
		void unselect();

		void SPIStackManager_setState(boolean state);

		boolean isSelected();
		boolean isUsingCustomSelectHandler();

		byte getID();
		byte getCsPin();
		byte getMark();
		
	private:
		boolean _state;
		byte _mark;
		byte _id;
		byte _csPin;
		boolean _useHandler;
		SPIStackableDevice_slaveSelectHandler _slaveSelectHandler;
};

#endif