
// @file           home_constants.cpp
// @author         flow@p0cki.at
// @date           11.2016
// @brief          define all constants

#ifndef _HOME_CONSTANTS_h
#define _HOME_CONSTANTS_h


//****** OUTPUT PINS ******
#define PIN_WS2812_1	5
#define PIN_WS2812_2	12
#define PIN_PWM_1		6
#define PIN_PWM_2		9

//****** INPUT PINS ******
#define	PIN_HUM_1		2
#define	PIN_TOUCH_2		4
#define	PIN_MOTION_1	3
#define	PIN_MOTION_2	7
#define PIN_SONIC_1		
#define PIN_SONIC_2
#define PIN_GAS_MQ135_1	A6
#define PIN_GAS_MQ7_1	A7
#define PIN_DUST_1		12

#define	NUM_LEDS_1		60
#define	NUM_LEDS_2		60

//****** DEFAULT *********
#define	DEFAULT_LOGLEVEL		debug
#define	DEFAULT_LOGTARGET		serial
#define	DEFAULT_LIGHTFDELAY		20
#define DEFAULT_THRESHOLD		0.5


// Definitionen der einzelnen Schaltzeiten
#define        laufzeit_10		10UL
#define        laufzeit_20		20UL
#define        laufzeit_30		30UL
#define        laufzeit_500		500UL
#define        laufzeit_1k		1000UL
#define        laufzeit_1k5		1500UL
#define        laufzeit_2k		2000UL
#define        laufzeit_5k		5000UL

#endif