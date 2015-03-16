#ifndef Tween_h
#define Tween_h

#include "Arduino.h"

class Tween
{
	public:
		Tween(int startValue, int endValue, unsigned long duration, unsigned long delay);
		Tween(int startValue, int endValue, unsigned long duration);

		void update(unsigned long deltaTime);

		void transition(int startValue, int endValue, unsigned long duration, unsigned long delay);
		void transition(int startValue, int endValue, unsigned long duration);
		void transitionTo(int endValue, unsigned long duration);
		void transitionTo(int endValue);

		long linearValue();
		long easeInValue();
		long easeOutValue();
		long easeInOutValue();

	private:
		boolean ended;
		int _startValue;
		int _endValue;
		unsigned long _duration;
		unsigned long _delay;
		unsigned long _currentTime;
		double _cursor;
};

#endif