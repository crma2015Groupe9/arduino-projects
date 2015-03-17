#ifndef RGBLed_h
#define RGBLed_h

#include "Arduino.h"

class RGBLed;
typedef void (*RGBLed_colorChangeHandler)(byte, byte, byte, byte, byte, byte, byte);

class RGBLed
{
	public:
		RGBLed(byte redPin, byte greenPin, byte bluePin, RGBLed_colorChangeHandler handler, byte mark);
		RGBLed(byte redPin, byte greenPin, byte bluePin, RGBLed_colorChangeHandler handler);
		RGBLed(byte redPin, byte greenPin, byte bluePin);
		RGBLed(RGBLed_colorChangeHandler handler, byte mark);

		void init(byte red, byte green, byte blue, byte intensity);
		void init(byte red, byte green, byte blue);
		void init();

		void changeColor(byte red, byte green, byte blue, byte intensity);
		void changeColor(byte red, byte green, byte blue);
		void i(byte intensity);
		void rgbi(byte red, byte green, byte blue, byte intensity);
		void rgb(byte red, byte green, byte blue);
		void r(byte red);
		void ri(byte red, byte intensity);
		void g(byte green);
		void gi(byte green, byte intensity);
		void b(byte blue);
		void bi(byte blue, byte intensity);
		void rg(byte red, byte green);
		void rgi(byte red, byte green, byte intensity);
		void rb(byte red, byte blue);
		void gb(byte green, byte blue);
		void rbi(byte red, byte blue, byte intensity);
		void gbi(byte green, byte blue, byte intensity);

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

		void lighter(byte value);
		void lighter();
		void darker(byte value);
		void darker();

		void off();
		void on();
		void toggle();

		byte getRed();
		byte getGreen();
		byte getBlue();
		byte getIntensity();
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
		byte _intensity;
		byte _calculNewValue(byte baseValue, byte addValue, byte lessValue);

		void _colorChange(byte red, byte green, byte blue);
		RGBLed_colorChangeHandler _colorChangeHandler;
		void _defaultColorChangeHandler(byte red, byte green, byte blue);
		byte _applyIntensity(byte value);
};

#endif