
// @file           home_arduino.ino
// @author         flow@p0cki.at
// @date           12.2016
// @brief          main routine

#include "FastLED.h"
#include "home_sensor.h"
#include "home_dout.h"
#include "home_actor.h"
#include "home_motion.h"
#include "home_constants.h"
#include "home_touch.h"
#include "home_aout.h"
#include "home_ain.h"
#include "Adafruit_NeoPixel.h"


	//*******************************************************
	//********************* DECLARATION *********************
	//*******************************************************
CRGB ledsA[NUM_LEDS_1];										// Erstelle Objekt: LED-Stripe
float ihue = 0;
float istep = 0.01;
int idelay = 0;
int bright = 1;

int numstops = round(255 / NUM_LEDS_1);

Adafruit_NeoPixel pixel = Adafruit_NeoPixel(NUM_LEDS_1, PIN_WS2812_1, NEO_GRB + NEO_KHZ800);


void LED_WS2812(int onoff)
{


	switch (onoff)
	{
	case 1:
		for (int i = 0;i < NUM_LEDS_1; i++)
		{
			ledsA[i] = CHSV(i*numstops + ihue, 255, 255);
			ihue += istep;
			if (ihue >= 255)
			{
				ihue = 0;
			}
		}
		break;
	default:
		for (int i = 0;i < NUM_LEDS_1; i++)
		{
			ledsA[i] = CHSV(0, 0, 0);
		}
		break;
	}
	LEDS.show();
	delay(idelay);
}

	//*******************************************************
	//************************ SETUP ************************
	//*******************************************************

void setup()
{
	Serial.begin(9600);

	LEDS.setBrightness(255);
	LEDS.addLeds<WS2812B, PIN_WS2812_1, GRB>(ledsA, NUM_LEDS_1);
	memset(ledsA, 0, NUM_LEDS_1 * sizeof(struct CRGB));


	/*pixel.begin();
	pixel.setPixelColor(5,pixel.Color(0,150,0));
	pixel.show();*/
}

	//*******************************************************
	//************************ LOOP *************************
	//*******************************************************
void loop()
{
	LED_WS2812(1);
}