#ifndef SDCardModule_h
#define SDCardModule_h

#include <SPI.h>
#include <SD.h>

#include "Arduino.h"

class SDCardModule
{
	public:
		SDCardModule(byte csPin);
		void init();

	private:
		byte _csPin;
};

#endif