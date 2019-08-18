#ifndef _HOME_RANDOMTEMPLIGHT_h
#define _HOME_RANDOMTEMPLIGHT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

// ACHTUNG: Alle Arduino Bibliotheken welche in anderen Klassen verwerdnet werden müssen zumindest zusätzlich auch hier inlcludet werden. Obwohl diese hier ausgegraut werden.
#include "FastLED.h"
#include "constants.h"
#include "logger.h"

float ihue = 0;
float istep = 0.01;
int idelay = 0;
int bright = 1;
int numstops = round(255 / NUM_LEDS_1);
CRGB ledsA[NUM_LEDS_1];
String previousColor;

inline CRGB* neopixelobjekt(int brightness, logger &logging_one)
{
	logging_one.writeLog("Setup WS2812B...", extremedebug);
	LEDS.setBrightness(brightness);
	LEDS.addLeds<WS2812B, PIN_WS2812_1, GRB>(ledsA, NUM_LEDS_1);
	memset(ledsA, 0, NUM_LEDS_1 * sizeof(struct CRGB));
	return ledsA;
}

inline void rainbow_effect(int onoff)
{
	switch (onoff)
	{
	case 1:
		//Serial.println("WS on");
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
		//Serial.println("WS off");
		for (int i = 0;i < NUM_LEDS_1; i++)
		{
			ledsA[i] = CHSV(0, 0, 0);
		}
		break;
	}
	LEDS.show();
	delay(idelay);
}

inline void LED_TempColor2(String color)
{
	int rnd[NUM_LEDS_1];
	int rndbright[NUM_LEDS_1];
	int quarterRange = NUM_LEDS_1 / 4;
	int ledsonpeak[NUM_LEDS_1 / 4];
	int ledsonlow[NUM_LEDS_1 / 4];
	int ledbright[NUM_LEDS_1 / 4];
	HSVHue colorium = {};


	Serial.print("Range= ");
	Serial.println(quarterRange);

	if (color == "arctic") { colorium = HUE_AQUA; }
	else if (color == "blue") { colorium = HUE_BLUE; }
	else if (color == "green") { colorium = HUE_GREEN; }
	else if (color == "yellow") { colorium = HUE_YELLOW; }
	else if (color == "orange") { colorium = HUE_ORANGE; }
	else if (color == "red") { colorium = HUE_RED; }

	// Randomwert für genutze Leds erzeugen
	for (int j = 0;j <= quarterRange; j++)
	{
		rnd[j] = rand() % NUM_LEDS_1;

		for (int i = 0;i <= quarterRange; i++)
		{
			if (rnd[j] == rnd[i])
			{
				rnd[j] = rand() % NUM_LEDS_1;
			}
		}

		Serial.print("Random= ");
		Serial.println(rnd[j]);
	}

	// Randomwert für Start-Helligkeit erzeugen
	for (int j = 0;j <= quarterRange; j++)
	{
		rndbright[j] = rand() % 255;

		Serial.print("RandomBright= ");
		Serial.println(rndbright[j]);
	}

	// Schleife für helligkeit Up
	for (int i = 0;i <= 255; i++)
	{
		Serial.print("brightnessUpLoop= ");
		Serial.println(i);
		for (int j = 0;j <= quarterRange; j++)
		{
			if (i <= rndbright[j])
			{
				ledsA[rnd[j]] = CHSV(colorium, 255, i);
			}

			if (i >= rndbright[j])
			{
				ledsA[rnd[j]] = CHSV(colorium, 255, rndbright[j] + 1);
				rndbright[j] = rndbright[j] + 1;
			}

			/*if (rndbright[j] + 1 <= 255)
			{
				ledsA[rnd[j]] = CHSV(colorium, 255, rndbright[j] + 1);

			}*/

			if (ledsonpeak[j] = rnd[j])
			{
				ledsA[rnd[j]] = CHSV(colorium, 255, i);
			}

			if (ledsonlow[j] = rnd[j])
			{

			}

			if (ledbright[j] = 255)
			{
				ledsonpeak[j] = rnd[j];
			}

			if (ledbright[j] = 0)
			{
				ledsonlow[j] = rnd[j];
			}

		}

		LEDS.show();
		delay(3);
	}

	delay(1);

	// Schleife für helligkeit Down
	for (int x = 255;x >= 0; x--)
	{
		Serial.print("brightnessDownLoop= ");
		Serial.println(x);

		for (int j = 0;j <= quarterRange; j++)
		{
			if (rndbright[j] - 1 >= 0)
			{
				ledsA[rnd[j]] = CHSV(colorium, 255, rndbright[j] - 1);
				rndbright[j] = rndbright[j] - 1;
			}
		}

		LEDS.show();
		delay(3);
	}
}

inline void LED_TempColor3(String color)
{
	int rndled;
	int number = NUM_LEDS_1 / 2;
	int range = NUM_LEDS_1;
	HSVHue colorium = {};

	if (color == "arctic") { colorium = HUE_AQUA; }
	else if (color == "blue") { colorium = HUE_BLUE; }
	else if (color == "green") { colorium = HUE_GREEN; }
	else if (color == "yellow") { colorium = HUE_YELLOW; }
	else if (color == "orange") { colorium = HUE_ORANGE; }
	else if (color == "red") { colorium = HUE_RED; }


	for (int j = 0;j <= number; j++)
	{
		rndled = rand() % range;

		for (int i = 0;i <= 255; i++)
		{
			ledsA[rndled] = CHSV(colorium, 255, i);
			LEDS.show();
			delay(3);
		}

		rndled = rand() % range;

		for (int x = 255;x >= 0; x--)
		{
			ledsA[rndled] = CHSV(colorium, 255, x);

			LEDS.show();
			delay(3);
		}
	}
}

inline void LED_TempColor4(String color)
{
	int rndledArray[NUM_LEDS_1];
	int led[NUM_LEDS_1];
	bool startswitch = true;
	int halfrange = NUM_LEDS_1 / 2;
	int range = NUM_LEDS_1;
	HSVHue colorium = {};

	int rndstart[NUM_LEDS_1];
	int lightupleds[NUM_LEDS_1];
	int lightoffleds[NUM_LEDS_1];


	if (color == "arctic") { colorium = HUE_AQUA; }
	else if (color == "blue") { colorium = HUE_BLUE; }
	else if (color == "green") { colorium = HUE_GREEN; }
	else if (color == "yellow") { colorium = HUE_YELLOW; }
	else if (color == "orange") { colorium = HUE_ORANGE; }
	else if (color == "red") { colorium = HUE_RED; }

	Serial.println("LED_TempColor");

	while (true)
	{

		if (startswitch == true)
		{

			for (int i = 0;i <= range; i++)
			{
				Serial.println("Init RND and Arrays");

				rndstart[i] = rand() % 255;
				rndledArray[i] = i;
				lightupleds[i] = NULL;
				lightoffleds[i] = NULL;
			}
		}

		if (startswitch == true)
		{
			for (int j = 0;j <= range; j++)
			{
				Serial.println("Init lightupleds");

				for (int i = 0;i <= 255; i++)
				{
					if (i == rndstart[j])
					{
						lightupleds[j] = rndledArray[j];
					}

					startswitch = false;
				}
			}
		}

		/*for (int j = 0;j <= range; j++)
		{
			for (int i = 0;i <= 255; i++)
			{
				if (i == rndstart[j])
				{
					lightupleds[j] = rndled[j];
				}

				delay(3);
			}
		}*/

		for (int blubb : lightupleds)
		{
			Serial.print("lightupleds loop = ");
			Serial.println(lightupleds[blubb]);

			if (lightupleds[blubb] != NULL)
			{
				if (rndstart[blubb] < 255)
				{
					//lightupleds[blubb] = lightupleds[blubb] + 1;
					rndstart[blubb] = rndstart[blubb] + 1;
					Serial.print("rndstart = ");
					Serial.println(rndstart[blubb]);
				}
				else
				{
					lightoffleds[blubb] = lightupleds[blubb];
					lightupleds[blubb] = NULL;
				}
			}
		}

		for (int blubb : lightoffleds)
		{
			Serial.print("lightoffleds loop = ");
			Serial.println(lightoffleds[blubb]);

			if (lightoffleds[blubb] != NULL)
			{
				if (rndstart[blubb] > 0)
				{
					//lightoffleds[blubb] = lightupleds[blubb] + 1;
					rndstart[blubb] = rndstart[blubb] - 1;
					Serial.print("rndstart = ");
					Serial.println(rndstart[blubb]);
				}
				else
				{
					lightupleds[blubb] = lightoffleds[blubb];
					lightoffleds[blubb] = NULL;
				}
			}
		}

		for (int blubb : rndstart)
		{
			Serial.println("show LEDS loop");
			Serial.println(rndstart[blubb]);

			ledsA[blubb] = CHSV(colorium, 255, rndstart[blubb]);
			LEDS.show();
		}
		delay(10);
	}
}

inline void LED_TempColor(String color)
{
	int range = NUM_LEDS_1;
	int blubb = 0;
	int fromblubb = 0;
	HSVHue colorium = {};

	if (color == "arctic") { colorium = HUE_AQUA; blubb = 128; }
	else if (color == "blue") { colorium = HUE_BLUE;  blubb = 160; }
	else if (color == "green") { colorium = HUE_GREEN;  blubb = 96; }
	else if (color == "yellow") { colorium = HUE_YELLOW; blubb = 64; }
	else if (color == "orange") { colorium = HUE_ORANGE; blubb = 32; }
	else if (color == "red") { colorium = HUE_RED; blubb = 0; }

	if (color != previousColor)
	{
		if (fromblubb < blubb)
		{
			for (int i = fromblubb;i <= blubb; i++)
			{
				//Serial.println("blubb++");
				//Serial.println(i);
				for (int element = 0;element <= range; element++)
				{
					//Serial.println("show leds");
					//Serial.println(element);
					ledsA[element] = CHSV(i, 255, 255);
				}
				LEDS.show();
			}
		}
		else
		{
			for (int i = fromblubb;i >= blubb; i--)
			{
				//Serial.println("blubb--");
				//Serial.println(i);
				for (int element = 0;element <= range; element++)
				{
					//Serial.println("show leds");
					//Serial.println(element);
					ledsA[element] = CHSV(i, 255, 255);
				}
				LEDS.show();
			}
		}
		fromblubb = blubb;
		previousColor = color;
	}
}
#endif