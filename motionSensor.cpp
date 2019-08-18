// @file      Motionsensor_one.h
// @author    flow@p0cki.net
// @date      01.2017
// @brief     childclass sensor


#include "motionSensor.h"
#include "constants.h"

motionSensor::motionSensor(String n, int p)
	:sensor(digitalIn_sens, n, p)
{

}

motionSensor::~motionSensor()
= default;

bool motionSensor::getValue(logger &logging_one)
{
	logging_one.writeLog("Call - motion - getValue", extremedebug);
	if (digitalRead(getPin()) == HIGH)
	{
		logging_one.writeLog("Motion: is true", sensordata);
		iMotionValue = true;
	}
	else
	{
		logging_one.writeLog("Motion: is false", sensordata);
		iMotionValue = false;
	}

/*
if (digitalRead(getPin()) == LOW && iMotionState != 0)
{
	iMotionState = 0;
	iMotionValue = false;
	Logging_one.writeLog("motion dedected...", sensordata);
}

if (digitalRead(getPin()) == HIGH && iMotionState != 1)
{
	iMotionState = 1;
	iMotionValue = true;
	Logging_one.writeLog("there is no motion...", sensordata);
}*/
		return iMotionValue;
}