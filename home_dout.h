// home_dout.h

#ifndef _HOME_DOUT_h
#define _HOME_DOUT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "home_actor.h"

class home_dout:public home_actor
{

public:
	 home_dout(String n, int p);
	 virtual ~home_dout();

	 virtual bool setValue(int v);

	 bool Doggle();

protected:


};

#endif

