
#ifndef _HOME_RANDOMLED_h
#define _HOME_RANDOMLED_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "FastLED.h"

class home_randomled
{

private:
	String previousColor;
	int rnd[NUM_LEDS_1];
	int rndbright[NUM_LEDS_1];
	int quarterRange = NUM_LEDS_1 / 4;
	int ledsonpeak[NUM_LEDS_1 / 4];
	int ledsonlow[NUM_LEDS_1 / 4];
	int ledbright[NUM_LEDS_1 / 4];

	int rndled{};
	int number = NUM_LEDS_1 / 2;
	int range = NUM_LEDS_1;
	HSVHue colorium = {};

	int rndledArray[NUM_LEDS_1];
	int led[NUM_LEDS_1];
	bool startswitch = true;
	int halfrange = NUM_LEDS_1 / 2;

	int blubb = 0;
	int fromblubb = 0;

	String thiscname;

public:
	home_randomled(String cname);
	~home_randomled();

	void LED_TempColor(String color);
	void LED_TempColor2(String color);
	void LED_TempColor3(String color);
	void LED_TempColor4(String color);
};
#endif