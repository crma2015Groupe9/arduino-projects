#include "Arduino.h"
#include "Potar.h"

Potar::Potar(byte pin, int inputMax, int outMin, int outMax){
	_pin = pin;
	_usePin = true;
	_inputMaxValue = inputMax;
	_outputMinValue = outMin;
	_outputMaxValue = outMax;
}

Potar::Potar(byte pin, int outMin, int outMax){
	_pin = pin;
	_usePin = true;
	_inputMaxValue = 1023;
	_outputMinValue = outMin;
	_outputMaxValue = outMax;
}

Potar::Potar(byte pin, int outMax){
	_pin = pin;
	_usePin = true;
	_inputMaxValue = 1023;
	_outputMinValue = 0;
	_outputMaxValue = outMax;
}

Potar::Potar(byte pin){
	_pin = pin;
	_usePin = true;
	_inputMaxValue = 1023;
	_outputMinValue = 0;
	_outputMaxValue = 255;
}

Potar::Potar(){
	_pin = 0;
	_usePin = false;
	_inputMaxValue = 1023;
	_outputMinValue = 0;
	_outputMaxValue = 255;
}

/*=======================*/

void Potar::init(){
	int temp, outputInterval;
	if (_outputMinValue > _outputMaxValue)
	{
		temp = _outputMinValue;
		_outputMinValue = _outputMaxValue;
		_outputMaxValue = temp;
	}
	outputInterval = _outputMaxValue - _outputMinValue;

	boolean outputIntervalIsPair = outputInterval % 2 == 0;

	if (_usePin){pinMode(_pin, INPUT);}
	_pinValue = _usePin ? analogRead(_pin) : 0;

	_middleValue1 = outputIntervalIsPair ? outputInterval/2 : (outputInterval+1)/2;
	_middleValue1 += _outputMinValue;
	_middleValue2 = outputIntervalIsPair ? _middleValue1+1 : _middleValue1;

	_currentValue = currentValue(_outputMinValue, _outputMaxValue);
	_previousValue = _currentValue;
}

void Potar::init(int inputMax, int outMin, int outMax){
	_inputMaxValue = inputMax;
	_outputMinValue = outMin;
	_outputMaxValue = outMax;
	init();
}

void Potar::init(int outMin, int outMax){
	init(_inputMaxValue, outMin, outMax);
}

void Potar::init(int outMax){
	init(_outputMinValue, outMax);
}

void Potar::update(int analogValue){
	_pinValue = _usePin ? analogRead(_pin) : analogValue;

	if(_pinValue>_inputMaxValue){_pinValue=_inputMaxValue;}
	if(_pinValue<0){_pinValue=0;}

	_previousValue = _currentValue;
	_currentValue = currentValue(_outputMinValue, _outputMaxValue);

	_valueChange = _currentValue != _previousValue;
	_valueGrewUp = _currentValue > _previousValue;
	_valueDecreased = _currentValue < _previousValue;
	_valueIsMax = _currentValue == _outputMaxValue;
	_valueIsMin = _currentValue == _outputMinValue;
}

void Potar::update(){
	update(0);
}

int Potar::currentValue(int min, int max){
	return map(_pinValue, 0, _inputMaxValue, min, max);
}

int Potar::currentValue(int max){
	return currentValue(0, max);
}

int Potar::currentValue(){
	return _currentValue;
}

boolean Potar::isCloseToMiddle(int toleranceLeft, int toleranceRight){
	int min = _middleValue1-toleranceLeft;
	int max = _middleValue2+toleranceRight;

	return (_currentValue >= min && _currentValue <= max);
}

boolean Potar::isCloseToMiddle(int tolerance){
	return isCloseToMiddle(tolerance, tolerance);
}

boolean Potar::isOnMiddle(){
	return isCloseToMiddle(0);
}

boolean Potar::isLow(){
	return _currentValue < _middleValue1;
}

boolean Potar::isHigh(){
	return _currentValue > _middleValue2;
}

boolean Potar::changed(){
	return _valueChange;
}

boolean Potar::grewUp(){
	return _valueGrewUp;
}

boolean Potar::decreased(){
	return _valueDecreased;
}

boolean Potar::isMin(){
	return _valueIsMin;
}

boolean Potar::isMax(){
	return _valueIsMax;
}