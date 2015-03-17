#include "Arduino.h"
#include "Tween.h"

Tween::Tween(int startValue, int endValue, unsigned long duration, unsigned long delay){
	_startValue = startValue;
	_endValue = endValue;
	_duration = duration;
	_delay = delay;
	_currentTime = 0;
	_cursor = 0;
	_ended = false;
	_ready = true;
	_pause = false;
	_loop = false;
	_loopWithDelay = false;
	_loopDelay = 0;
	_loopCount = 0;
	_maxNumberOfLoop = 0;
}

Tween::Tween(int startValue, int endValue, unsigned long duration){
	_startValue = startValue;
	_endValue = endValue;
	_duration = duration;
	_delay = 0;
	_currentTime = 0;
	_cursor = 0;
	_ended = false;
	_ready = true;
	_pause = false;
	_loop = false;
	_loopWithDelay = false;
	_loopDelay = 0;
	_loopCount = 0;
	_maxNumberOfLoop = 0;
}

Tween::Tween(){
	_startValue = 0;
	_endValue = 0;
	_duration = 0;
	_delay = 0;
	_currentTime = 0;
	_cursor = 0;
	_ended = false;
	_ready = false;
	_pause = false;
	_loop = false;
	_loopWithDelay = false;
	_loopDelay = 0;
	_loopCount = 0;
	_maxNumberOfLoop = 0;
}

void Tween::update(unsigned long deltaTime){
	if (_ready && !_ended)
	{
		_currentTime += _pause ? 0 : deltaTime;
		if (_currentTime > _delay)
		{
			_cursor = (double)(_currentTime - _delay)/(double)_duration;
		}

		if (_currentTime >= _duration+_delay){
			_cursor = 1;
			_currentTime = _duration+_delay;
			_ended = true;

			if(_loop && (_maxNumberOfLoop == 0 || (_loopCount+1) < _maxNumberOfLoop)){
				_ended = false;
				_ready = true;
				_currentTime = 0;
				_delay = _loopWithDelay ? _loopDelay : _delay;
				_loopCount++;
			}
		}
	}
}

void Tween::transition(int startValue, int endValue, unsigned long duration, unsigned long delay){
	_startValue = startValue;
	_endValue = endValue;
	_duration = duration;
	_delay = delay;
	_currentTime = 0;
	_cursor = 0;
	_ended = false;
	_ready = true;
	_loop = false;
	_loopWithDelay = false;
	_loopDelay = 0;
	_loopCount = 0;
	_maxNumberOfLoop = 0;
}

void Tween::loop(unsigned int numberOfLoop){
	_loop = true;
	_loopWithDelay = false;
	_maxNumberOfLoop = numberOfLoop;
	_loopCount = 0;
}

void Tween::addLoop(unsigned int numberOfLoop){
	_maxNumberOfLoop += numberOfLoop;
}

void Tween::addLoop(){
	addLoop(1);
}

void Tween::loop(){
	loop(0);
}

void Tween::loopWithDelay(){
	loopWithDelay(_delay);
}

void Tween::loopWithDelay(unsigned long delay){
	_loop = true;
	_loopWithDelay = true;
	_loopDelay = delay;
	_maxNumberOfLoop = 0;
	_loopCount = 0;
}

void Tween::loopWithDelay(unsigned long delay, unsigned int numberOfLoop){
	loopWithDelay(delay);
	_maxNumberOfLoop = numberOfLoop;
}

unsigned int Tween::loopCount(){
	return _loopCount;
}

boolean Tween::isEnded(){
	return _ended;
}

void Tween::stopLoop(){
	_loop = false;
}

void Tween::pause(){
	_pause = true;
}

void Tween::play(){
	_pause = false;
}

void Tween::reset(){
	_currentTime = _delay;
	_ended = false;
}

void Tween::replay(){
	reset();
	play();
}

void Tween::replayWithDelay(unsigned long delay){
	_delay = delay;
	replayWithDelay();
}

void Tween::replayWithDelay(){
	resetWithDelay();
	play();
}

void Tween::resetWithDelay(unsigned long delay){
	_delay = delay;
	resetWithDelay();
}

void Tween::resetWithDelay(){
	_currentTime = 0;
	_ended = false;
}

void Tween::stop(boolean restartBeforeDelay){
	pause();
	restartBeforeDelay ? resetWithDelay() : reset();
}

void Tween::stop(){
	stop(false);
}

void Tween::transition(int startValue, int endValue, unsigned long duration){
	transition(startValue, endValue, duration, 0);
}

void Tween::transitionTo(int endValue, unsigned long duration){
	transition((int)linearValue(), endValue, duration);
}

void Tween::transitionTo(int endValue){
	transitionTo(endValue, (_ended ? 0 : (_duration+_delay) - _currentTime));
}

long Tween::_applyEaseFactor(double _easeFactor){
	return (long)((double)_startValue+(_easeFactor*(double)(_endValue - _startValue)));
}

/*=======================*/

long Tween::linearValue(){
	return _applyEaseFactor(easeNone(_cursor));
};
long Tween::easeInQuadValue(){
	return _applyEaseFactor(easeInQuad(_cursor));
};
long Tween::easeOutQuadValue(){
	return _applyEaseFactor(easeOutQuad(_cursor));
};
long Tween::easeInOutQuadValue(){
	return _applyEaseFactor(easeInOutQuad(_cursor));
};
long Tween::easeInCubicValue(){
	return _applyEaseFactor(easeInCubic(_cursor));
};
long Tween::easeOutCubicValue(){
	return _applyEaseFactor(easeOutCubic(_cursor));
};
long Tween::easeInOutCubicValue(){
	return _applyEaseFactor(easeInOutCubic(_cursor));
};
long Tween::easeInQuartValue(){
	return _applyEaseFactor(easeInQuart(_cursor));
};
long Tween::easeOutQuartValue(){
	return _applyEaseFactor(easeOutQuart(_cursor));
};
long Tween::easeInOutQuartValue(){
	return _applyEaseFactor(easeInOutQuart(_cursor));
};
long Tween::easeInQuintValue(){
	return _applyEaseFactor(easeInQuint(_cursor));
};
long Tween::easeOutQuintValue(){
	return _applyEaseFactor(easeOutQuint(_cursor));
};
long Tween::easeInOutQuintValue(){
	return _applyEaseFactor(easeInOutQuint(_cursor));
};

double Tween::easeNone(double t){
	return t;
}
double Tween::easeInQuad(double t){
	return t*t;
}
double Tween::easeOutQuad(double t){
	return t*(2.00-t);
}
double Tween::easeInOutQuad(double t){
	return t<0.50 ? 2.00*t*t : -1.00+(4.00-2.00*t)*t;
}
double Tween::easeInCubic(double t){
	return t*t*t;
}
double Tween::easeOutCubic(double t){
	return (--t)*t*t+1.00;
}
double Tween::easeInOutCubic(double t){
	return t<0.50 ? 4.00*t*t*t : (t-1.00)*(2.00*t-2.00)*(2.00*t-2.00)+1.00;
}
double Tween::easeInQuart(double t){
	return t*t*t*t;
}
double Tween::easeOutQuart(double t){
	return 1-(--t)*t*t*t;
}
double Tween::easeInOutQuart(double t){
	return t<0.50 ? 8.00*t*t*t*t : 1.00-8.00*(--t)*t*t*t;
}
double Tween::easeInQuint(double t){
	return t*t*t*t*t;
}

double Tween::easeOutQuint(double t){
	return 1.00+(--t)*t*t*t*t;
}

double Tween::easeInOutQuint(double t){
	return t<0.50 ? 16.00*t*t*t*t*t : 1.00+16.00*(--t)*t*t*t*t;
}