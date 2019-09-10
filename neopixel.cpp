// @file           neopixel.cpp
// @author         flow@p0cki.net
// @date           09.2019
// @brief          neopixel Class

#include "neopixel.h"
#include "FastLED.h"

neopixel::neopixel(String name, int pin, int numleds)
	:actor(WS2812_act, name, pin)
{
	numleds_ = numleds;
	ledsA_[numleds];
	numstops_ = round(255 / numleds);
}

neopixel::~neopixel()
{
}

bool neopixel::setAllLikeInput(int led, int hue, int saturation, int brightness)
{
	if (led != -1)
	{
		ledsA_[led] = CHSV(hue_, saturation_, brightness_);
	}
	else
	{
		for (int element = 0;element <= numleds_; element++)
		{
			ledsA_[element] = CHSV(hue_, saturation_, brightness_);
		}
	}
	LEDS.show();
}

// Legt alle Werte fest
// wird led "-1" übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird eine LED geschalten.
bool neopixel::setValues(int led, int hue, int saturation, int brightness, logger &log)
{
	log.writeLog("Call - neopixel - setValues", extremedebug);
	saturation_ = saturation;
	hue_ = hue;
	brightness_ = brightness;
	setAllLikeInput(led, hue_, saturation_, brightness_);
	return true;
}

// Legt die Farbsättigung fest
// wird led "-1" übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird eine LED geschalten.
bool neopixel::setSaturation(int led, int saturation, logger &log)
{
	log.writeLog("Call - neopixel - setSaturation", extremedebug);
	saturation_ = saturation;
	setAllLikeInput(led, hue_, saturation_, brightness_);
	return true;
}

// Legt die Farbe fest
// wird led "-1" übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird eine LED geschalten.
bool neopixel::setHue(int led, int hue, logger &log)
{
	log.writeLog("Call - neopixel - setHue", extremedebug);
	hue_ = hue;
	setAllLikeInput(led, hue_, saturation_, brightness_);
	return true;
}

// Legt dide Helligkeit fest
// wird led "-1" übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird eine LED geschalten.
bool neopixel::setBrightness(int led, int brightness, logger &log)
{
	log.writeLog("Call - neopixel - setBrightness", extremedebug);
	brightness_ = brightness;
	setAllLikeInput(led, hue_, saturation_, brightness_);
	return true;
}

// Initialisiert den Ledstripe
CRGB* neopixel::InitNeoPixel(int brightness, int saturation, logger &log)
{
	log.writeLog("Setup WS2812...", debug);
	brightness_ = brightness;
	saturation_ = saturation;
	LEDS.setBrightness(0);
	LEDS.clear();
	LEDS.clearData();
	LEDS.setBrightness(brightness_);
	LEDS.setBrightness(saturation_);
	LEDS.addLeds<WS2812B, PIN_WS2812_1, GRB>(ledsA_, numleds_);
	memset(ledsA_, 0, numleds_ * sizeof(struct CRGB));
	return ledsA_;
}


// Helligkeit langsam erhöhen oder veringern - je nach dem ob der Input True oder False ist.
// wird led "-1" übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird eine LED geschalten.
void neopixel::SlowlyIncreaseOrDecreaseBrightness(int led, bool sensorResult, int maxBrightness, logger& log)
{
	log.writeLog("Call - SlowlyIncreaseOrDecreaseValue", extremedebug);

	if (sensorResult == true)
	{
		if (lightcounter_ != maxBrightness)
		{
			if (lightcounter_ < maxBrightness)
			{
				lightcounter_++;
				log.writeLog("Value Up - " + String(lightcounter_), extremedebug);
			}
		}
	}
	else
	{
		if (lightcounter_ != 0)
		{
			if (lightcounter_ > 0)
			{
				lightcounter_--;
				log.writeLog("Value Down - " + String(lightcounter_), extremedebug);
			}
		}
	}
	setBrightness(led, lightcounter_, log);
}

// Farbänderung zu angegebenen Farbe
void neopixel::fadeToTargetColor(int hue, logger &log)
{
	log.writeLog("Call - fadeToTargetColor", debug);

	/*if (fadeHue != fadeHuePrev)
	{
		fadeHue = hue;
	}
	else
	{
		fadeHue = fadeHuePrev;
	}*/

	if (hue != previousColor_)
	{
		if (fromblubb_ < blubb_)
		{
			for (int i = fromblubb_;i <= blubb_; i++)
			{
				log.writeLog("TColor - blubb++: " + String(i), extremedebug);
				for (int element = 0;element <= range_; element++)
				{
					//Logging_one.writeLog("TColor - show leds: " + String(element), extremedebug);
					ledsA_[element] = CHSV(i, 255, 255);
				}
				LEDS.show();
			}
		}
		else
		{
			for (int i = fromblubb_;i >= blubb_; i--)
			{
				log.writeLog("TColor - blubb--: " + String(i), extremedebug);
				for (int element = 0;element <= range_; element++)
				{
					//Logging_one.writeLog("TColor - show leds: " + String(element), extremedebug);
					ledsA_[element] = CHSV(i, 255, 255);
				}
				LEDS.show();
			}
		}
		fromblubb_ = blubb_;
		previousColor_ = colorium_;
	}
}