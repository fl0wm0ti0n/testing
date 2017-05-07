
// @file           home_arduino.cpp
// @author         flow@p0cki.at
// @date           12.2016
// @brief          main routine

#include "home_sensor.h"
#include "home_dout.h"
#include "home_actor.h"
#include "home_motion.h"
#include "home_doggle.h"
#include "home_constants.h"
#include "home_touch.h"
//#include <FastLED.h>

/*
	//*******************************************************
	//********************* DECLARATION *********************
	//*******************************************************
home_touch touch_1;											// Erstelle Objekt: Touchsensor
home_doggle doggle_1;										// Erstelle Objekt: Switch

CRGB ledsA[NUM_LEDS_1];										// Erstelle Objekt: LED-Stripe
float ihue = 0;
float istep = 0.01;
int idelay = 0;
int bright = 1;

int numstops = round(255 / NUM_LEDS_1);


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
	*/
void setup()
{
	
	/*Serial.begin(9600);
	Serial.println("main:setup aufgerufen");

	//********************* RGB LEDs ***********************
	LEDS.setBrightness(255);
	LEDS.addLeds<WS2812B, PIN_WS2812_1, GRB>(ledsA, NUM_LEDS_1);
	memset(ledsA, 0, NUM_LEDS_1 * sizeof(struct CRGB));


	//********************** Touchy ************************
	//touch_1.setPin(PIN_TOUCH_1);
	*/
}


	//*******************************************************
	//************************ LOOP *************************
	//*******************************************************
void loop()
{
	home_dout schnickschnack("schnick", 13);
	while (true)
	{
		schnickschnack.Doggle();
		delay(500);
	}
	//********************** Touch? ************************

	/*int bFlipValue = doggle_1.flip(touch_1.getValue());

	Serial.println("loop: Value:");
	Serial.println(bFlipValue);

		if (bFlipValue)
		{
			LED_WS2812(1);
			Serial.println("loop: On");
		}
		else
		{
			LED_WS2812(0);
			Serial.println("loop: Off");
		}
		delay(50);
		*/


}

