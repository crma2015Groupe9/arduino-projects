#include "Arduino.h"
#include "SPIDigitalPot.h"


SPIDigitalPot::SPIDigitalPot(byte csPin, byte numberOfChannels){
	_reverseMode = false;
	_csPin = csPin;
	_numberOfChannels = numberOfChannels;
	_selectedChannel = 1;
}

SPIDigitalPot::SPIDigitalPot(byte csPin){
	_reverseMode = false;
	_csPin = csPin;
	_numberOfChannels = 6;
	_selectedChannel = 1;
}

void SPIDigitalPot::init(byte* startValues, byte numberOfInitializedChannels){
	pinMode(_csPin, OUTPUT);
	digitalWrite(_csPin, HIGH);

	multipleWrite(startValues, numberOfInitializedChannels);
}

void SPIDigitalPot::init(byte* startValues){
	init(startValues, _numberOfChannels);
}

void SPIDigitalPot::init(){
	pinMode(_csPin, OUTPUT);
	digitalWrite(_csPin, HIGH);

	writeForAll(0);
}

boolean SPIDigitalPot::selectChannel(byte channel){
	return selectChannel(channel, false);
}

boolean SPIDigitalPot::selectChannel(byte channel, byte loop){
	if (channel >= 0 && channel <= _numberOfChannels)
	{
		_selectedChannel = channel;
		return true;
	}
	else if (loop){
		return selectChannel(channel - _numberOfChannels, true);
	}
	return false;
}

boolean SPIDigitalPot::firstChannel(){
	selectChannel(1);
}

boolean SPIDigitalPot::lastChannel(){
	selectChannel(_numberOfChannels);
}

void SPIDigitalPot::off(){
	selectChannel(0);
}

void SPIDigitalPot::on(byte startChannel){
	selectChannel(startChannel);
}

void SPIDigitalPot::on(){
	on(1);
}

boolean SPIDigitalPot::previousChannel(boolean loop){
	return lowerChannel(1, loop);
}

boolean SPIDigitalPot::previousChannel(){
	return previousChannel(false);
}

boolean SPIDigitalPot::nextChannel(boolean loop){
	return greaterChannel(1, loop);
}

boolean SPIDigitalPot::nextChannel(){
	return nextChannel(false);
}

boolean SPIDigitalPot::lowerChannel(byte jump, boolean loop){
	byte diff;
	if (!loop)
	{
		return selectChannel(_selectedChannel-jump);
	}
	if (_selectedChannel >= jump)
	{
		return selectChannel(_selectedChannel-jump, true);
	}

	diff = jump - _selectedChannel;
	while(diff > _numberOfChannels){
		diff -= _numberOfChannels;
	}

	return selectChannel(_numberOfChannels-diff, loop);
}

boolean SPIDigitalPot::lowerChannel(byte jump){
	return lowerChannel(jump, false);
}

boolean SPIDigitalPot::lowerChannel(){
	return lowerChannel(1);
}

boolean SPIDigitalPot::greaterChannel(byte jump, boolean loop){
	if (((int)_selectedChannel+(int)jump) > 255)
	{
		return false;
	}
	return selectChannel(_selectedChannel+jump, loop);
}

boolean SPIDigitalPot::greaterChannel(byte jump){
	return greaterChannel(jump, false);
}

boolean SPIDigitalPot::greaterChannel(){
	return greaterChannel(1);
}

void SPIDigitalPot::write(byte channel, byte value){
	if (selectChannel(channel))
	{
		write(value);
	}
}

void SPIDigitalPot::write(byte value){
	if (_selectedChannel > 0)
	{
		digitalWrite(_csPin,LOW);
	  	SPI.transfer(_selectedChannel-1);
	  	SPI.transfer(_reverseMode ? 255-value : value);
	  	digitalWrite(_csPin,HIGH);
	}
}

void SPIDigitalPot::writeForAll(byte value){
	byte i;
	for(i=1;i<=_numberOfChannels;i++){
		write(i, value);
	}
}

void SPIDigitalPot::multipleWrite(byte* values, byte numberOfWritedChannels){
	byte i;

	for(i=1;i<=numberOfWritedChannels;i++){
		write(i, values[i-1]);
	}
}

void SPIDigitalPot::multipleWrite(byte* values){
	multipleWrite(values, _numberOfChannels);
}

byte SPIDigitalPot::selectedChannel(){
	return _selectedChannel;
}

void SPIDigitalPot::reverseMode(){
	_reverseMode = true;
}

void SPIDigitalPot::regularMode(){
	_reverseMode = false;
}