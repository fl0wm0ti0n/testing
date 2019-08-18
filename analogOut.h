// home_dout.h

#ifndef _HOME_AOUT_h
#define _HOME_AOUT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "actor.h"

class analogOut :public actor
{

public:
	analogOut(String n, int p);
	virtual ~analogOut();

	virtual bool setValue(int v);

	bool doggle();
};

#endif

