// @file           analogOut.cpp
// @author         flow@p0cki.net
// @date           08.2019
// @brief          class for analog output

#include "analogOut.h"
#include "logger.h"

analogOut::analogOut(String n, int p)
	:actor(digitalOut_act, n, p)
{
	actor::setValue(analogRead(p));
}

analogOut::~analogOut()
= default;

bool analogOut::setValue(int v, logger &Logging_one)
{
	Logging_one.writeLog("Call - analogOut - setValue", extremedebug);
	if (getValue() != v)
	{
		//actor::setValue(v);
		analogWrite(getPin(), v);
	}
	return true;
}

bool analogOut::doggle(logger &Logging_one)
{
	Logging_one.writeLog("Call - analogOut - doggle", extremedebug);
	return setValue(!getValue(), Logging_one);
}