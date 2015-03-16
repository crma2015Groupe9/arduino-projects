#ifndef PushButton_h
#define PushButton_h

#include "Arduino.h"

class PushButton
{
	public:
		PushButton(byte pin);
		PushButton();
		void init(boolean defaultValue);
		void init();
		void update(boolean digitalValue);
		void update();

		boolean isPressed();
		boolean clickDown();
		boolean clickUp();
	private:
		byte _pin;
		boolean _defaultValue;
		boolean _usePin;
		boolean _pinValue;
		boolean _waitForPush;
		boolean _clickDown;
		boolean _clickUp;
};

#endif