// 
// 
// 

#include "home_ain.h"

home_ain::home_ain(String n, int p)
	:home_sensor(tSensorType::analogIn_sens, n, p)
{
	home_sensor::getValue(analogRead(p));
	setPin(p);
}

home_ain::~home_ain()
= default;

int home_ain::setPin(int iPin)
{
	iPinNum = iPin;
	pinMode(iPinNum, INPUT);
}

int home_ain::getValue()
{
	iAnalogValue = analogRead(iPinNum);
	return iAnalogValue;
}