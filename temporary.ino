#include "home_pins.h"
#include "home_touch.h"
#include <FastLED.h>

#define DATA_PIN    6
#define NUM_LEDS    60
#define TOUCH_DATA_PIN	2 // Pin for capactitive touch sensor
#define IR_PIN		3 // Pin for IR-Sensor

//*******************************************************
//********************* DECLARATION *********************
//*******************************************************

CRGB ledsA[NUM_LEDS];
float ihue = 0;
float istep = 0.01;
int idelay = 0;
int bright = 1;

int numstops = round(255 / NUM_LEDS);


//*******************************************************
//*********************** WS2812 ************************
//*******************************************************
void LED_WS2812(int onoff)
{

	switch (onoff)
	{
	case 1:
		for (int i = 0;i < NUM_LEDS; i++)
		{
			ledsA[i] = CHSV(i*numstops + ihue, 255, 255);
			ihue += istep;
			if (ihue >= 255)
			{
				ihue = 0;
			}
		}
		break;
	case 0:
		for (int i = 0;i < NUM_LEDS; i++)
		{
			ledsA[i] = CHSV(0, 0, 0);
		}
		break;
	default:
		for (int i = 0;i < NUM_LEDS; i++)
		{
			ledsA[i] = CHSV(0, 0, 0);
		}
		break;
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

	//********************* RGB LEDs ***********************
	LEDS.setBrightness(255);
	LEDS.addLeds<WS2812B, DATA_PIN, GRB>(ledsA, NUM_LEDS);
	memset(ledsA, 0, NUM_LEDS * sizeof(struct CRGB));

	//********************** Touchy ************************
	Serial.begin(9600);
	pinMode(TOUCH_DATA_PIN, INPUT);
}


//*******************************************************
//************************ LOOP *************************
//*******************************************************
void loop()
{
	bool flip = false;

	//********************** Touchy ************************
	int ctsValue = digitalRead(TOUCH_DATA_PIN);

	if (ctsValue == HIGH)
	{
		flip = !flip;
	}

	if (flip == true)
	{
		LED_WS2812(1);
		Serial.println("Touched");
	}
	else
	{
		LED_WS2812(0);
		Serial.println("not touched");
	}
	delay(500);

}

