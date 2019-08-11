// home_ain.h

#ifndef _HOME_AIN_h
#define _HOME_AIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "home_sensor.h"

class home_ain : public home_sensor
{
	private:
		int iAnalogValue;
		int	iPinNum;

	public:
		home_ain(String n, int p);			// Constructor
		virtual ~home_ain();				// Destructor

		int getValue();						// Method: get Value
		int setPin(int iPin);				// Method: set Pin
};

#endif