#include "Arduino.h"
#include "TimeManager.h"

TimeManager::TimeManager(){
}

void TimeManager::init(){
	_time = millis();
	_previousTime = _time;
	_deltaTime = 0;
}

void TimeManager::loopStart(){
	_time = millis();
	_deltaTime = _time >= _previousTime ? _time - _previousTime : (ULONG_MAX - _previousTime + _time);
}

void TimeManager::loopEnd(){
	_previousTime = _time;
}

unsigned long TimeManager::total(){
	return _time;
}

unsigned long TimeManager::delta(){
	return _deltaTime;
}