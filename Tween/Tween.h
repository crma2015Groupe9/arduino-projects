#ifndef Tween_h
#define Tween_h

#include "Arduino.h"

class Tween
{
	public:
		Tween(int startValue, int endValue, unsigned long duration, unsigned long delay);
		Tween(int startValue, int endValue, unsigned long duration);
		Tween();

		void update(unsigned long deltaTime);

		void transition(int startValue, int endValue, unsigned long duration, unsigned long delay);
		void transition(int startValue, int endValue, unsigned long duration);
		void transitionTo(int endValue, unsigned long duration);
		void transitionTo(int endValue);

		long linearValue();
  		long easeInQuadValue();
  		long easeOutQuadValue();
  		long easeInOutQuadValue();
  		long easeInCubicValue();
  		long easeOutCubicValue();
  		long easeInOutCubicValue();
  		long easeInQuartValue();
  		long easeOutQuartValue();
  		long easeInOutQuartValue();
  		long easeInQuintValue();
  		long easeOutQuintValue();
  		long easeInOutQuintValue();

  		double easeNone(double t);
  		double easeInQuad(double t);
  		double easeOutQuad(double t);
  		double easeInOutQuad(double t);
  		double easeInCubic(double t);
  		double easeOutCubic(double t);
  		double easeInOutCubic(double t);
  		double easeInQuart(double t);
  		double easeOutQuart(double t);
  		double easeInOutQuart(double t);
  		double easeInQuint(double t);
  		double easeOutQuint(double t);
  		double easeInOutQuint(double t);

		void pause();
		void play();
		void reset();
		void replay();
		void replayWithDelay(unsigned long delay);
		void replayWithDelay();
		void resetWithDelay(unsigned long delay);
		void resetWithDelay();
		void stop(boolean restartBeforeDelay);
		void stop();

	private:
		boolean _ended;
		boolean _ready;
		boolean _pause;
		int _startValue;
		int _endValue;
		unsigned long _duration;
		unsigned long _delay;
		unsigned long _currentTime;
		double _cursor;

		long _applyEaseFactor(double _easeFactor);
};

#endif