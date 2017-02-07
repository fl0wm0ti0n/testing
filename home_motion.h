// home_motion.h

#ifndef _HOME_MOTION_h
#define _HOME_MOTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class home_motion
{

private:
	int iMotionValue;
	int	iPinNum;
	int iMotionState;

public:
	home_motion();						// Constructor
	virtual ~home_motion();				// Destructor

	int getAnalog();					// Method: get Touch Analog Value
	int getValue();						// Method: get Touch Value
	int setPin(int iPin);				// Method: set Touch Pin


};

#endif

