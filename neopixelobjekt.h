#ifndef _HOME_NEOPIXELOBJEKT_h
#define _HOME_NEOPIXELOBJEKT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "FastLED.h"
#include "constants.h"

/*inline CRGB* neopixelobjekt(int brightness)
{
	static CRGB ledsA[NUM_LEDS_1];
	LEDS.setBrightness(brightness);
	LEDS.addLeds<WS2812B, PIN_WS2812_1, GRB>(ledsA, NUM_LEDS_1);
	memset(ledsA, 0, NUM_LEDS_1 * sizeof(struct CRGB));
	return ledsA;
}*/
#endif