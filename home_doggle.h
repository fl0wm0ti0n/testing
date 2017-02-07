
// @file           home_doggle.h
// @author         flow@p0cki.at
// @date           12.2016
// @brief          flip a Value

#ifndef _HOME_DOGGLE_h
#define _HOME_DOGGLE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class home_doggle
{
private:
	static int iflip;
	static int iflop;
	bool iReturnValue;

public:
	home_doggle();						// Constructor
	virtual ~home_doggle();				// Destructor

	int flip(int iValue);				// Method: get on or off					
};
#endif

