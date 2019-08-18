// @file           home_touch.cpp
// @author         flow@p0cki.at
// @date           11.2016
// @brief          touch sensor Values

#include "touchSensor.h"

touchSensor::touchSensor(String n, int p)
	:sensor(digitalIn_sens, n, p)
{

}

touchSensor::~touchSensor()
= default;

// Gibt den Status des Sensors als Boolean zurück.
bool touchSensor::getState(logger &logging_one)
{
	logging_one.writeLog("Call - touch - getValue", extremedebug);
	if (digitalRead(getPin()) == HIGH)
	{
		logging_one.writeLog("Touch: is true", sensordata);
		bTouchState = true;
	}
	else
	{
		logging_one.writeLog("Touch: is false", sensordata);
		bTouchState = false;
	}
	return bTouchState;
}

// Wechselt, wenn sich der Status des Sensors geändert hat. den Boolean als Doggle zwischen True und False und gibt den gewechselten Status als Boolean zurück.
bool touchSensor::getStateWithDoggle(logger &logging_one)
{
	logging_one.writeLog("Call - touch - getValueWithDoggle", extremedebug);
	if (digitalRead(getPin()) == HIGH && iDigitalValue != 0)
	{
		logging_one.writeLog("Touch: is false", sensordata);
		iDigitalValue	= 0;
		bTouchState		= false;
	}
	if (digitalRead(getPin()) == HIGH && iDigitalValue != 1)
	{
		logging_one.writeLog("Touch: is true", sensordata);
		iDigitalValue	= 1;
		bTouchState		= true;
	}
	return bTouchState; 
}

// Gibt den analogen Wert des Sensors zurück.
float touchSensor::getAnalog(t_analog_or_bool tswitch, logger &logging_one)
{

	logging_one.writeLog("Call - touch - getAnalog", extremedebug);
	fAnalogValue = analogRead(getPin());

	if (fAnalogValue >= fThreshold)
	{
		bTouchState = true;
	}
	else
	{;
		bTouchState = false;
	}

	// Schalter ob boolean oder Analog zurückgegeben wird.
	if (tswitch == booleanReturn)
	{
		return bTouchState;
	}
	logging_one.writeLog("Touch: Analoger Wert = " + String(fAnalogValue), sensordata);
	return fAnalogValue;
}

// Wechselt, wenn sich der Status des Sensors geändert hat. den Boolean als Doggle zwischen True und False und gibt den gewechselten Status als Boolean zurück.
float touchSensor::getAnalogWithDoggle(t_analog_or_bool tswitch, logger &logging_one)
{
	logging_one.writeLog("Call - touch - getAnalogWithDoggle", extremedebug);
	fAnalogValue = analogRead(getPin());
	if (fAnalogValue >= fThreshold && iDigitalValue != 0)
	{
		iDigitalValue	= 0;
		bTouchState		= false;
		logging_one.writeLog("Touch: is false", sensordata);
	}
	if (fAnalogValue >= fThreshold && iDigitalValue != 1)
	{
		iDigitalValue	= 1;
		bTouchState		= true;
		logging_one.writeLog("Touch: is true", sensordata);
	}

	// Schalter ob boolean oder Analog zurückgegeben wird.
	if (tswitch == booleanReturn)
	{
		return bTouchState;
	}
	logging_one.writeLog("Touch: Analoger Wert = " + String(fAnalogValue), sensordata);
	return fAnalogValue;
}

void touchSensor::setAnalogTreshold(float threshold, logger &logging_one)
{
	logging_one.writeLog("Call - touch - setAnalogTreshold", extremedebug);
	fThreshold = threshold;
}