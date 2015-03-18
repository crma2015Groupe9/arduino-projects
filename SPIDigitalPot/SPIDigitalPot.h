#ifndef SPIDigitalPot_h
#define SPIDigitalPot_h

/*
	Need SPI lib ->
	#include <SPI.h>
*/

#include <SPI.h>
#include "Arduino.h"

class SPIDigitalPot
{
	public:
		SPIDigitalPot(byte csPin);
		SPIDigitalPot(byte csPin, byte numberOfChannels);

		void init();
		void reverseMode();
		void regularMode();

		void off();
		void on(byte startChannel);
		void on();

		boolean selectChannel(byte channel);
		boolean selectChannel(byte channel, byte loop);
		boolean firstChannel();
		boolean lastChannel();

		boolean previousChannel(boolean loop);
		boolean previousChannel();
		boolean nextChannel(boolean loop);
		boolean nextChannel();

		boolean lowerChannel(byte jump, boolean loop);
		boolean lowerChannel(byte jump);
		boolean lowerChannel();
		boolean greaterChannel(byte jump, boolean loop);
		boolean greaterChannel(byte jump);
		boolean greaterChannel();

		void write(byte channel, byte value);
		void write(byte value);
		void writeForAll(byte value);
		void multipleWrite(byte* values, byte numberOfWritedChannels);
		void multipleWrite(byte* values);

		byte selectedChannel();

	private:
		byte _reverseMode;
		byte _csPin;
		byte _numberOfChannels;
		byte _selectedChannel;
};

#endif