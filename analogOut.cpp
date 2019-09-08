// @file           analogOut.cpp
// @author         flow@p0cki.net
// @date           08.2019
// @brief          class for analog output

#include "analogOut.h"
#include "logger.h"

analogOut::analogOut(String n, int p)
	:actor(analogOut_act, n, p)
{
	actor::setValue(analogRead(p));
}

analogOut::~analogOut()
= default;

bool analogOut::setValue(int v, logger &log)
{
	log.writeLog("Call - analogOut - setValue", extremedebug);

	if (getValue() != v)
	{
		actor::setValue(v);
		analogWrite(getPin(), v);
	}
	return true;
}

bool analogOut::doggle(logger &log)
{
	log.writeLog("Call - analogOut - doggle", extremedebug);
	return setValue(!getValue(), Logging_one);
}

void analogOut::SlowlyIncreaseOrDecreaseValue(bool o_sensor, int o_actor, logger &log)
{
	log.writeLog("Call - lichtAnSolangeInputImpulsAn", extremedebug);

	if (o_sensor == true)
	{
		if (lightcounter != 255)
		{
			if (lightcounter < 255)
			{
				lightcounter++;
				log.writeLog("Licht an - " + String(lightcounter), debug);
			}
		}
	}
	else
	{
		if (lightcounter != 0)
		{
			if (lightcounter > 0)
			{
				lightcounter--;
				log.writeLog("Licht aus - " + String(lightcounter), debug);
			}
		}
	}
	setValue(lightcounter, log);
}