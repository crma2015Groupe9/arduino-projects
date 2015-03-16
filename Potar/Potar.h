#ifndef Potar_h
#define Potar_h

#include "Arduino.h"

class Potar
{
	public:
		Potar(byte pin, int inputMax, int outMin, int outMax);
		Potar(byte pin, int outMin, int outMax);
		Potar(byte pin, int outMax);
		Potar(byte pin);
		Potar();

		void init(int inputMax, int outMin, int outMax);
		void init(int outMin, int outMax);
		void init(int outMax);
		void init();
		void update(int analogValue);
		void update();

		int currentValue(int min, int max);
		int currentValue(int max);
		int currentValue();

		boolean isCloseToMiddle(int toleranceLeft, int toleranceRight);
		boolean isCloseToMiddle(int tolerance);
		boolean isOnMiddle();
		boolean isLow();
		boolean isHigh();
		boolean changed();
		boolean grewUp();
		boolean decreased();
		boolean isMin();
		boolean isMax();

	private:
		byte _pin;
		boolean _usePin;

		int _pinValue;
		int _currentValue;
		int _previousValue;

		int _inputMaxValue;
		int _outputMinValue;
		int _outputMaxValue;
		int _middleValue1;
		int _middleValue2;

		boolean _valueChange;
		boolean _valueGrewUp;
		boolean _valueDecreased;
		boolean _valueIsMax;
		boolean _valueIsMin;
};

#endif