// digitalOut.h

#ifndef _HOME_DOUT_h
#define _HOME_DOUT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "actor.h"

class digitalOut:public actor
{

public:
	 digitalOut(String n, int p);
	 virtual ~digitalOut();

	 virtual bool setValue(int v);

	 bool doggle();
};

#endif

