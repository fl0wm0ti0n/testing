
// @file           home_constants.cpp
// @author         flow@p0cki.at
// @date           11.2016
// @brief          define all constants

#ifndef _HOME_CONSTANTS_h
#define _HOME_CONSTANTS_h


//****** OUTPUT PINS ******
#define PIN_WS2812_1	6
#define PIN_WS2812_2	12
#define PIN_PWM_1		5
#define PIN_PWM_2		9
#define PIN_PWM_3		9
#define PIN_PWM_4		10
#define PIN_PWM_5		11

//****** INPUT PINS ******
#define	PIN_HUM_1		2
#define	PIN_TOUCH_2		4
#define	PIN_MOTION_1	3
#define	PIN_MOTION_2	7
#define PIN_SONIC_1		
#define PIN_SONIC_2

#define	NUM_LEDS_1		60
#define	NUM_LEDS_2		60

//****** Konfig ******
#define DELAY_LIGHT_UP		70
#define DELAY_LIGHT_DOWN	70

/* 
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class home_pins
{
private:
	int iPinX;

public:
	home_pins(int iPin);				// Constructor
	virtual ~home_pins();					// Destructor

	int getPin();						// Method: get Touch Value
	int setPin();						// Method: get Touch Value
};

*/

#endif


