
// @file           home_arduino.ino
// @author         flow@p0cki.at
// @date           12.2016
// @brief          main routine

#include <FastLED.h>
#include "home_sensor.h"
#include "home_dout.h"
#include "home_actor.h"
#include "home_motion.h"
#include "home_doggle.h"
#include "home_constants.h"
#include "home_touch.h"
#include "home_aout.h"
#include "DHT.h"


	//*******************************************************
	//********************* DECLARATION *********************
	//*******************************************************
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

void setup()
{
	Serial.begin(9600);
	home_aout light2("light2", PIN_PWM_1);

	home_dout light1("light1", PIN_PWM_2);

	home_motion motion1("motion1", PIN_MOTION_1);
	Serial.println("Start");

	LEDS.setBrightness(255);
	LEDS.addLeds<WS2812B, PIN_WS2812_1, GRB>(ledsA, NUM_LEDS_1);
	memset(ledsA, 0, NUM_LEDS_1 * sizeof(struct CRGB));

	DHT dht(PIN_HUM_1, DHT22);

	dht.begin();

	while (true)
	{
		Serial.println("Schleife");
		if (motion1.getValue(PIN_MOTION_1) == true)
		{
			if (light2.getValue() != 255)
			{
				Serial.println("On");
				for (int i = 1; i <= 255; ++i)
				{
					light2.setValue(i);
					delay(20);
				}
				light2.setValue(255);
				LED_WS2812(1);
			}
		}
		else
		{
			if (light2.getValue() != 0)
			{
				Serial.println("Off");
				for (int j = 255; j >= 0; --j)
				{
					light2.setValue(j);
					delay(20);
				}
				light2.setValue(0);
				LED_WS2812(0);
			}
		}

		float temp = dht.readTemperature();
		float hum = dht.readHumidity();

		Serial.print("Temperatur: ");
		Serial.print(temp);
		Serial.print("°C, ");
		Serial.print("Feuchtigkeit: ");
		Serial.print(hum);
		Serial.println("%");

		delay(500);
	}
}

	//*******************************************************
	//************************ LOOP *************************
	//*******************************************************
void loop()
{

}

