#include "Arduino.h"
#include "SPIDigitalPot.h"

SPIDigitalPot::SPIDigitalPot(byte csPin, byte numberOfChannels, SPIDigitalPot_slaveSelectHandler handler, byte mark){
	_reverseMode = false;
	_csPin = csPin;
	_numberOfChannels = numberOfChannels;
	_selectedChannel = 1;
	_mark = mark;
	_slaveSelectUseHandler = true;
	_slaveSelectHandler = handler;
}

SPIDigitalPot::SPIDigitalPot(byte csPin, byte numberOfChannels, SPIDigitalPot_slaveSelectHandler handler){
	_reverseMode = false;
	_csPin = csPin;
	_numberOfChannels = numberOfChannels;
	_selectedChannel = 1;
	_mark = 0;
	_slaveSelectUseHandler = true;
	_slaveSelectHandler = handler;
}

SPIDigitalPot::SPIDigitalPot(byte csPin, byte numberOfChannels){
	_reverseMode = false;
	_csPin = csPin;
	_numberOfChannels = numberOfChannels;
	_selectedChannel = 1;
	_mark = false;
	_slaveSelectUseHandler = false;
}

SPIDigitalPot::SPIDigitalPot(byte csPin, SPIDigitalPot_slaveSelectHandler handler, byte mark){
	_reverseMode = false;
	_csPin = csPin;
	_numberOfChannels = 6;
	_selectedChannel = 1;
	_mark = mark;
	_slaveSelectUseHandler = true;
	_slaveSelectHandler = handler;
}

SPIDigitalPot::SPIDigitalPot(byte csPin, SPIDigitalPot_slaveSelectHandler handler){
	_reverseMode = false;
	_csPin = csPin;
	_numberOfChannels = 6;
	_selectedChannel = 1;
	_mark = 0;
	_slaveSelectUseHandler = true;
	_slaveSelectHandler = handler;
}

SPIDigitalPot::SPIDigitalPot(byte csPin){
	_reverseMode = false;
	_csPin = csPin;
	_numberOfChannels = 6;
	_selectedChannel = 1;
	_mark = 0;
	_slaveSelectUseHandler = false;
}
		
SPIDigitalPot::SPIDigitalPot(SPIDigitalPot_slaveSelectHandler handler, byte mark){
	_reverseMode = false;
	_csPin = 0;
	_numberOfChannels = 6;
	_selectedChannel = 1;
	_mark = mark;
	_slaveSelectUseHandler = true;
	_slaveSelectHandler = handler;
}

SPIDigitalPot::SPIDigitalPot(SPIDigitalPot_slaveSelectHandler handler, byte mark, byte numberOfChannels){
	_reverseMode = false;
	_csPin = 0;
	_numberOfChannels = numberOfChannels;
	_selectedChannel = 1;
	_mark = mark;
	_slaveSelectUseHandler = true;
	_slaveSelectHandler = handler;
}

void SPIDigitalPot::init(){
	pinMode(_csPin, OUTPUT);
	digitalWrite(_csPin, HIGH);
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
		_slaveSelectUseHandler ? _slaveSelectHandler(LOW, _csPin, _mark) : digitalWrite(_csPin,LOW);
	  	SPI.transfer(_selectedChannel-1);
	  	SPI.transfer(_reverseMode ? 255-value : value);
	  	_slaveSelectUseHandler ? _slaveSelectHandler(HIGH, _csPin, _mark) : digitalWrite(_csPin,HIGH);
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