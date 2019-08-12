// @file           home_arduino.ino
// @author         flow@p0cki.at
// @date           12.2016
// @brief          main routine

#include <DHT.h>
#include "home_sensor.h"
#include "home_dout.h"
#include "home_actor.h"
#include "home_motion.h"
#include "home_doggle.h"
#include "home_constants.h"
#include "home_touch.h"
#include "home_aout.h"
#include "home_dht.h"
#include "home_ain.h"
#include "randomtemplight.h"
#include "neopixelobjekt.h"
#include "home_gas.h"
#include "home_log.h"

//*******************************************************
//********************* DECLARATION *********************
//*******************************************************

int lightcounter = 0;
int lightdoggle = 0;
int lightswitch = 1;

home_log logging_one(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, "Logging1");
home_aout lightStripe("lightstripe 1", PIN_PWM_2);
home_motion motionSensor("motionsensor 1", PIN_MOTION_1);
home_dht dhtSensor("dhtsensor 1", PIN_HUM_1);
home_gas gasSensor("gassensor 1 - MQ135", PIN_GAS_MQ135_1);
home_gas gasSensor2("gassensor 2 - MQ7", PIN_GAS_MQ7_1);

// Variablen deklarieren in denen die Startzeiten
// der einzelnen Zeitfunktionen gespeichert werden
unsigned long startzeit_1 = 0;
unsigned long startzeit_2 = 0;
unsigned long startzeit_3 = 0;
unsigned long startzeit_4 = 0;
unsigned long startzeit_5 = 0;

// Definitionen der einzelnen Schaltzeiten
#define        laufzeit_10		10UL
#define        laufzeit_20		20UL
#define        laufzeit_30		30UL
#define        laufzeit_500		500UL
#define        laufzeit_1k		1000UL
#define        laufzeit_1k5		1500UL
#define        laufzeit_2k		2000UL
#define        laufzeit_5k		5000UL

void LichtKomplettSchalten_SobaldImpuls()
{
	// Wenn Bewegung "light up" bis das Licht ganz an ist nach einer am Motionsensor eingestellten Zeit geht das licht wieder aus.

	if (motionSensor.getValue(PIN_MOTION_1) == true)
	{
		if (lightStripe.getValue() != 255)
		{
			Serial.println("On");
			Serial.println(lightStripe.getValue());

			for (int i = 0; i <= 255; ++i)
			{
				lightStripe.setValue(i);
				delay(20);
			}
			lightStripe.setValue(255);
		}
	}
	else
	{
		if (lightStripe.getValue() != 0)
		{
			Serial.println("Off");
			Serial.println(lightStripe.getValue());
			for (int j = 255; j >= 0; --j)
			{
				lightStripe.setValue(j);
				delay(20);
			}
			lightStripe.setValue(0);
		}
	}
}

void LichtAnSolangeInputImpulsAn()
{
	// Wenn Bewegung "light up" - sobald keine Bewegung "light down"
	// Impuls effect
	// Mit Motionsensor justierbar

	if (motionSensor.getValue(PIN_MOTION_1) == true)
	{
		if (lightStripe.getValue() != 255)
		{
			Serial.println("On");
			Serial.println(lightStripe.getValue());
			if (lightStripe.getValue() <= 255)
			{
				Serial.println(lightcounter);
				lightcounter++;
				lightStripe.setValue(lightcounter);
			}
		}
	}
	else
	{
		if (lightStripe.getValue() != 0)
		{
			Serial.println("Off");
			Serial.println(lightStripe.getValue());
			if (lightStripe.getValue() >= 0)
			{
				lightcounter--;
				Serial.println(lightcounter);
				lightStripe.setValue(lightcounter);
			}
		}
	}
}

void LichtAnSolangeInputImpulsAn_AusErlaubtNach255()
{
	// Wenn Bewegung "light up" bis volle Stärke - erst danach "light off"
	// NICHT mit Motionsensor justierbar
	
		if (lightStripe.getValue() != 255 && lightdoggle == 0)
		{
			if (lightStripe.getValue() <= 255 && motionSensor.getValue(PIN_MOTION_1) == true)
			{
				/*Serial.print("On1 = ");
				Serial.println(lightcounter);*/
				lightcounter++;
				lightStripe.setValue(lightcounter);
				lightdoggle = 0;
				lightswitch = 0;
			}
			else if (lightcounter <= 255 && motionSensor.getValue(PIN_MOTION_1) == false)
			{
				/*Serial.print("On2 = ");
				Serial.println(lightcounter);*/
				lightStripe.setValue(lightcounter);
				if (lightswitch == 0) { lightcounter++;}
			}
		}
		else
		{
			lightdoggle = 1;
		}

		if (lightStripe.getValue() != 0 && lightdoggle == 1 && motionSensor.getValue(PIN_MOTION_1) == false)
		{
			if (lightStripe.getValue() > 0)
			{
				/*Serial.print("Off = ");
				Serial.println(lightcounter);*/
				lightcounter--;
				lightStripe.setValue(lightcounter);
				lightdoggle = 1;
				lightswitch = 1;
			}
		}
		else
		{
			lightdoggle = 0;
		}
}

void motionCheck()
{
	//LichtAnSolangeInputImpulsAn_AusErlaubtNach255();
	LichtAnSolangeInputImpulsAn();
	//LichtKomplettSchalten_SobaldImpuls();
}

void dhtCheck()
{
	logging_one.writeLog("Checking DHT ...", debug);

	float hum = dhtSensor.getHumValueOnlyIfChanged();
	float temp = dhtSensor.getTempValueOnlyIfChanged();

	if (			  temp	<= 20 && hum <= 50)	{ LED_TempColor("arctic"); }
	if (temp >	20 && temp	<= 23 && hum <= 50) { LED_TempColor("blue"); }
	if (temp >	23 && temp	<= 25 && hum >	55)	{ LED_TempColor("green"); }
	if (temp >	25 && temp	<= 27 && hum >= 60) { LED_TempColor("yellow"); }
	if (temp >	27 && temp	<= 30 && hum >= 70) { LED_TempColor("orange"); }
	if (temp >	30				  && hum >= 80) { LED_TempColor("red"); }
}

	//*******************************************************
	//************************ SETUP ************************
	//*******************************************************
void setup()
{
	logging_one.writeLog("Setup Begin", debug);

	neopixelobjekt(255);

	logging_one.writeLog("Setup End", debug);
}

	//*******************************************************
	//************************ LOOP *************************
	//*****************s**************************************
void loop()
{
	// laufzeit_1 EIN, laufzeit_1 AUS - LED schalten in loop - Schaltzeiten in Millisekunden
	if (millis() - startzeit_1 >= laufzeit_20)
	{
		startzeit_1 = millis();
		motionCheck();
	}

	if (millis() - startzeit_2 >= laufzeit_500)
	{
		startzeit_2 = millis();
		dhtCheck();
	}
}