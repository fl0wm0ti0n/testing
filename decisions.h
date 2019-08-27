// @file           actor.h
// @author         flow@p0cki.net
// @date           01.2017
// @brief          baseclass of all actors

#ifndef _DECISION_h
#define _DECISION_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "logger.h"

enum t_decision_type
{
	undefined		= 0,
	lightOn			= 1,
	servoOn 		= 2,
	colorChange		= 3,
	toEffect		= 4
};

class decisions
{

private:

	t_decision_type	m_iType;
	String m_cName;

	// Variablen f�r Lichtklassen
	int lightcounter = 0;
	int lightdoggle = 0;
	int lightswitch = 1;

public:
	decisions(t_decision_type t, String n);
	virtual ~decisions();

	int LichtKomplettSchalten_SobaldImpuls(bool o_sensor, int o_actor, logger &Logging_one);
	int LichtAnSolangeInputImpulsAn(bool o_sensor, int o_actor, logger &Logging_one);
	int LichtAnSolangeInputImpulsAn_AusErlaubtNach255(bool o_sensor, int o_actor, logger &Logging_one);

	t_decision_type getType()
	{
		return m_iType;
	}

	String getName()
	{
		return m_cName;
	}
};
#endif