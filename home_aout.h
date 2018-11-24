// home_aout.h

#ifndef _HOME_AOUT_h
#define _HOME_AOUT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "home_actor.h"

class home_aout :public home_actor
{

public:
	home_aout(String n, int p);
	virtual ~home_aout();

	virtual bool setValue(int v);

	bool doggle();
};

#endif

