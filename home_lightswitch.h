// home_lighswitch.h

#ifndef _HOME_LIGHTSWITCH_h
#define _HOME_LIGHTSWITCH_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "home_aout.h"
#include "home_motion.h"

class home_lightswitch
{
		int i_switch_;
		int i_analog_value_;
		home_aout	light_;
		home_motion	motion_;


	public:					
		home_lightswitch(home_aout lightin, home_motion motionin);  // Constructor
		virtual ~home_lightswitch();								// Destructor

		bool SwitchLight();					// Method: get Touch Analog Value
};

#endif