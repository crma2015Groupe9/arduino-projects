#ifndef RGBLed_h
#define RGBLed_h

#include "Arduino.h"

class RGBLed;
typedef void (*colorChangeHandler)(byte, byte, byte, byte, byte, byte, byte);

class RGBLed
{
	public:
		RGBLed(byte redPin, byte greenPin, byte bluePin, colorChangeHandler handler, byte mark);
		RGBLed(byte redPin, byte greenPin, byte bluePin, colorChangeHandler handler);
		RGBLed(byte redPin, byte greenPin, byte bluePin);
		RGBLed(colorChangeHandler handler, byte mark);

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

		void moreRed(byte value);
		void moreRed();
		void lessRed(byte value);
		void lessRed();

		void moreGreen(byte value);
		void moreGreen();
		void lessGreen(byte value);
		void lessGreen();

		void moreBlue(byte value);
		void moreBlue();
		void lessBlue(byte value);
		void lessBlue();

		void off();
		void on();
		void toggle();

		byte getRed();
		byte getGreen();
		byte getBlue();
		byte mark();

	private:
		byte _redPin;
		byte _greenPin;
		byte _bluePin;
		boolean _useHandler;
		byte _mark;

		boolean _on;

		byte _red;
		byte _green;
		byte _blue;
		byte _calculNewValue(byte baseValue, byte addValue, byte lessValue);

		void _colorChange(byte red, byte green, byte blue);
		colorChangeHandler _colorChangeHandler;
		void _defaultColorChangeHandler(byte red, byte green, byte blue);
};

#endif