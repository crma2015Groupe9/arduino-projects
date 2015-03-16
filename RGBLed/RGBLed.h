#ifndef RGBLed_h
#define RGBLed_h

#include "Arduino.h"

class RGBLed;
typedef void (*colorChangeHandler)(byte, byte, byte);

class RGBLed
{
	public:
		RGBLed(byte redPin, byte greenPin, byte bluePin, colorChangeHandler handler);
		RGBLed(byte redPin, byte greenPin, byte bluePin);
		RGBLed(colorChangeHandler handler);

		void init(byte red, byte green, byte blue);
		void init();

		void changeColor(byte red, byte green, byte blue);
		void rgb(byte red, byte green, byte blue);
		void r(byte red);
		void g(byte green);
		void b(byte blue);
		void rg(byte red, byte green);
		void rb(byte red, byte blue);
		void gb(byte green, byte blue);

		byte getRed();
		byte getGreen();
		byte getBlue();

	private:
		byte _redPin;
		byte _greenPin;
		byte _bluePin;
		boolean _useHandler;

		byte _red;
		byte _green;
		byte _blue;

		colorChangeHandler _colorChangeHandler;
		void _defaultColorChangeHandler(byte red, byte green, byte blue);
};

#endif