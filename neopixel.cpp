#include "neopixel.h"

neopixel::neopixel(String name, int pin, int numleds)
	:actor(WS2812_act, name, pin)
{
	this->numleds_ = numleds;
	this->ledsA_[numleds];
	numstops_ = round(255 / numleds);
}

neopixel::~neopixel()
{
}

bool neopixel::setAllLikeInput(int led, int hue, int saturation, int brightness)
{

	if (led != 0)
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
// wird led NULL übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird einde LED geschalten.
bool neopixel::setValues(int led, int hue, int saturation, int brightness)
{
	saturation_ = saturation;
	hue_ = hue;
	brightness_ = brightness;
	setAllLikeInput(led, hue_, saturation_, brightness_);
	return true;
}

// Legt die Farbsättigung fest
// wird led NULL übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird einde LED geschalten.
bool neopixel::setSaturation(int led, int saturation)
{
	saturation_ = saturation;
	setAllLikeInput(led, hue_, saturation_, brightness_);
	return true;
}

// Legt die Farbe fest
// wird led NULL übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird einde LED geschalten.
bool neopixel::setHue(int led, int hue)
{
	hue_ = hue;
	setAllLikeInput(led, hue_, saturation_, brightness_);
	return true;
}

// Legt dide Helligkeit fest
// wird led NULL übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird einde LED geschalten.
bool neopixel::setBrightness(int led, int brightness)
{
	brightness_ = brightness;
	setAllLikeInput(led, hue_, saturation_, brightness_);
	return true;
}

// Initialisiert den Ledstripe
CRGB* neopixel::InitNeoPixel(int brightness, logger &log)
{
	brightness_ = brightness;

	log.writeLog("Setup WS2812B...", debug);
	LEDS.setBrightness(brightness_);
	LEDS.addLeds<WS2812B, PIN_WS2812_1, GRB>(ledsA_, numleds_);
	memset(ledsA_, 0, numleds_ * sizeof(struct CRGB));
	return ledsA_;
}

// Helligkeit lang
void neopixel::SlowlyBrightness(int maxBrightgness, logger &log)
{

}

// Farbänderung zu angegebenen Farbe
void neopixel::fadeToTargetColor(int hue, logger &log)
{
	log.writeLog("Call - WS2812_FadeToTargetColor", debug);

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