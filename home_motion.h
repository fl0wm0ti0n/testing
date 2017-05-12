// home_motion.h

#ifndef _HOME_MOTION_h
#define _HOME_MOTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "home_sensor.h"

class home_motion :public home_sensor
{

public:
	home_motion(String n, int p);		// Constructor
	virtual ~home_motion();				// Destructor

	virtual bool getValue(int v);		// Method: get motion Value


protected:

};

#endif

