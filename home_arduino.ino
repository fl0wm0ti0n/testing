// @file           home_arduino.ino
// @author         flow@p0cki.at
// @date           12.2016
// @brief          main routine

#include <DHT.h>
#include "home_actor.h"
#include "home_motion.h"
#include "home_constants.h"
#include "home_aout.h"
#include "home_dht.h"
#include "randomtemplight.h"
#include "home_gas.h"
#include "home_log.h"
#include "Streaming.h"

//*******************************************************
//********************* DECLARATION *********************
//*******************************************************

int lightcounter = 0;
int lightdoggle = 0;
int lightswitch = 1;

home_log logging_one(extremedebug, DEFAULT_LOGTARGET, "Logging1");
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

void LichtKomplettSchalten_SobaldImpuls()
{
	logging_one.writeLog("Funktionsaufruf - LichtKomplettSchalten_SobaldImpuls", extremedebug);
	// Wenn Bewegung "light up" bis das Licht ganz an ist nach einer am Motionsensor eingestellten Zeit geht das licht wieder aus.

	if (motionSensor.getValue(PIN_MOTION_1, logging_one) == true)
	{
		if (lightStripe.getValue() != 255)
		{
			for (int i = 0; i <= 255; ++i)
			{
				lightStripe.setValue(i);
				delay(DEFAULT_LIGHTFDELAY);
				logging_one.writeLog("Licht an - " + String(lightStripe.getValue()), debug);
			}
			lightStripe.setValue(255);
		}
	}
	else
	{
		if (lightStripe.getValue() != 0)
		{

			for (int j = 255; j >= 0; --j)
			{
				lightStripe.setValue(j);
				delay(DEFAULT_LIGHTFDELAY);
				logging_one.writeLog("Licht aus - " + String(lightStripe.getValue()), debug);
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

	String lightvalue;

	logging_one.writeLog("Call - LichtAnSolangeInputImpulsAn", extremedebug);

	if (motionSensor.getValue(PIN_MOTION_1, logging_one) == true)
	{
		if (lightStripe.getValue() != 255)
		{
			if (lightStripe.getValue() <= 255)
			{
				lightcounter++;
				lightStripe.setValue(lightcounter);
				lightvalue = String(lightStripe.getValue());
				logging_one.writeLog("Licht an - " + lightvalue, debug);
			}
		}
	}
	else
	{
		if (lightStripe.getValue() != 0)
		{
			if (lightStripe.getValue() >= 0)
			{
				lightcounter--;
				lightStripe.setValue(lightcounter);
				lightvalue = String(lightStripe.getValue());
				logging_one.writeLog("Licht aus - " + lightvalue, debug);
			}
		}
	}
}

void LichtAnSolangeInputImpulsAn_AusErlaubtNach255()
{
	logging_one.writeLog("Funktionsaufruf - LichtAnSolangeInputImpulsAn_AusErlaubtNach255", extremedebug);
	// Wenn Bewegung "light up" bis volle Stärke - erst danach "light off"
	// NICHT mit Motionsensor justierbar
	
		if (lightStripe.getValue() != 255 && lightdoggle == 0)
		{
			if (lightStripe.getValue() <= 255 && motionSensor.getValue(PIN_MOTION_1, logging_one) == true)
			{
				logging_one.writeLog(&"Licht an - "[lightcounter], debug);

				lightcounter++;
				lightStripe.setValue(lightcounter);
				lightdoggle = 0;
				lightswitch = 0;
			}
			else if (lightcounter <= 255 && motionSensor.getValue(PIN_MOTION_1, logging_one) == false)
			{
				logging_one.writeLog(&"Licht an - "[lightcounter], debug);

				lightStripe.setValue(lightcounter);
				if (lightswitch == 0) { lightcounter++;}
			}
		}
		else
		{
			lightdoggle = 1;
		}

		if (lightStripe.getValue() != 0 && lightdoggle == 1 && motionSensor.getValue(PIN_MOTION_1, logging_one) == false)
		{
			if (lightStripe.getValue() > 0)
			{
				logging_one.writeLog(&"Licht aus - "[lightcounter], debug);

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
	logging_one.writeLog("Call - motionCheck", extremedebug);
	//LichtAnSolangeInputImpulsAn_AusErlaubtNach255();
	LichtAnSolangeInputImpulsAn();
	//LichtKomplettSchalten_SobaldImpuls();
}

void dhtCheck()
{
	logging_one.writeLog("Call - dhtCheck", extremedebug);
	float hum = dhtSensor.getHumValueOnlyIfChanged(logging_one);
	float temp = dhtSensor.getTempValueOnlyIfChanged(logging_one);

	if (			  temp	<= 20 && hum <= 50)	{ LED_TempColor("arctic");	logging_one.writeLog("Set color 'arctic'", debug); }
	if (temp >	20 && temp	<= 23 && hum <= 50) { LED_TempColor("blue");	logging_one.writeLog("Set color 'blue'", debug); }
	if (temp >	23 && temp	<= 25 && hum >	55)	{ LED_TempColor("green");	logging_one.writeLog("Set color 'green'", debug); }
	if (temp >	25 && temp	<= 27 && hum >= 60) { LED_TempColor("yellow");  logging_one.writeLog("Set color 'yellow'", debug); }
	if (temp >	27 && temp	<= 30 && hum >= 70) { LED_TempColor("orange");  logging_one.writeLog("Set color 'orange'", debug); }
	if (temp >	30				  && hum >= 80) { LED_TempColor("red");		logging_one.writeLog("Set color 'red'", debug); }
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
	//*******************************************************
void loop()
{

	/*if (millis() - startzeit_3 >= laufzeit_1k)
	{

		sClock = millis() / 1000;

		if (sClock + 1 >= sClockOld);
		{
			sekunde++;
			sClockOld = sClock;
			if (sekunde = 60)
			{
				minute++;
				sekunde = 0;
				if (minute = 60)
				{
					stunde++;
					minute = 0;
				}
			}
		}
	}*/

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