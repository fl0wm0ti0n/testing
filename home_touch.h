// home_touch.h

#ifndef _HOME_TOUCH_h
#define _HOME_TOUCH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class home_touch
{
	private:
		int iSwitch;
		int iTouchValue;
		int	iPinNum;

	public:
		home_touch();						// Constructor
		virtual ~home_touch();				// Destructor

		int getAnalog();					// Method: get Touch Analog Value
		int getValue();						// Method: get Touch Value
		int setPin(int iPin);				// Method: set Touch Pin
};

#endif

