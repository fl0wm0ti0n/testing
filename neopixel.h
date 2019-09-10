#ifndef _NEOPIXEL_h
#define _NEOPIXEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "actor.h"
#include "FastLED.h"
#include "constants.h"
#include "logger.h"

class neopixel :
	public actor
{

private:
	float	ihue_ = 0;
	float	istep_ = 0.01;
	int		idelay_ = 0;
	int		bright_ = 1;
	int		numstops_ = 0;
	int		numleds_ = 0;

	int		saturation_ = 0;
	int		hue_ = 0;
	int		brightness_ = 0;

	CRGB	ledsA_[NUM_LEDS_1];

	HSVHue	previousColor_;
	int		range_ = numleds_;
	int		blubb_ = 0;
	int		fromblubb_ = 0;
	HSVHue	colorium_ = {};
	String	color_;
	int		fade_hue_ = 0;
	int		fade_hue_prev_ = 0;
	int		lightcounter_ = 0;

	bool setAllLikeInput(int led, int hue, int saturation, int brightness);

public:
	neopixel(String n, int p, int numleds);
	virtual ~neopixel();
	bool setValues(int led, int hue, int sat, int val, logger &log);	// wird led NULL �bergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird einde LED geschalten.
	bool setSaturation(int led, int saturation, logger &log);
	bool setHue(int led, int hue, logger &log);
	bool setBrightness(int led, int brightness, logger &log);
	void fadeToTargetColor(int hue, logger &log);		// �ndert die aktuell�e farbe zu einer zielfarbe
	CRGB* InitNeoPixel(int brightness, int saturation, logger &log);
	void SlowlyIncreaseOrDecreaseBrightness(int led, bool sensorResult, int maxBrightness, logger& log);

	int GetHue()
	{
		return hue_;
	}
	int GetSaturation()
	{
		return saturation_;
	}

	int GetBrightness()
	{
		return brightness_;
	}

	int GetNumleds()
	{
		return numleds_;
	}
};
#endif