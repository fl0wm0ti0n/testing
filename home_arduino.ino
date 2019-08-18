// @file           home_arduino.ino
// @author         flow@p0cki.at
// @date           12.2016
// @brief          main routine

#include "FastLED.h"
#include <DHT.h>
#include "actor.h"
#include "motionSensor.h"
#include "constants.h"
#include "analogOut.h"
#include "dhtSensor.h"
#include "randomtemplight.h"
#include "gasSensor.h"
#include "logger.h"

//*******************************************************
//********************* DECLARATION *********************
//*******************************************************

// Objekte welche sofort benötigt werden.
logger Logging_one(extremedebug, DEFAULT_LOGTARGET, "Logging1");
analogOut LightStripe_one("lightstripe 1", PIN_PWM_2);
motionSensor Motionsensor_one("motionsensor 1", PIN_MOTION_1);
dhtSensor DHTSensor_one("dhtsensor 1", PIN_HUM_1);
//gasSensor gasSensor("gassensor 1 - MQ135", PIN_GAS_MQ135_1);
//gasSensor gasSensor2("gassensor 2 - MQ7", PIN_GAS_MQ7_1);

// Variablen für Lichtklassen
int lightcounter = 0;
int lightdoggle = 0;
int lightswitch = 1;

// Variablen deklarieren in denen die Startzeiten
// der einzelnen Zeitfunktionen gespeichert werden
unsigned long startzeit_1 = 0;
unsigned long startzeit_2 = 0;
unsigned long startzeit_3 = 0;
unsigned long startzeit_4 = 0;
unsigned long startzeit_5 = 0;

// Wenn Bewegung "light up" bis das Licht ganz an ist nach einer am Motionsensor eingestellten Zeit geht das licht wieder aus.
// Mainloop und millis unabhängig (alles muss auf diesen Prozess warten)
void LichtKomplettSchalten_SobaldImpuls()
{
	Logging_one.writeLog("Call - LichtKomplettSchalten_SobaldImpuls", extremedebug);

	if (Motionsensor_one.getValue(Logging_one) == true)
	{
		if (LightStripe_one.getValue() != 255)
		{
			for (int i = 0; i <= 255; ++i)
			{
				LightStripe_one.setValue(i);
				delay(DEFAULT_LIGHTFDELAY);
				Logging_one.writeLog("Licht an - " + String(LightStripe_one.getValue()), debug);
			}
			LightStripe_one.setValue(255);
		}
	}
	else
	{
		if (LightStripe_one.getValue() != 0)
		{

			for (int j = 255; j >= 0; --j)
			{
				LightStripe_one.setValue(j);
				delay(DEFAULT_LIGHTFDELAY);
				Logging_one.writeLog("Licht aus - " + String(LightStripe_one.getValue()), debug);
			}
			LightStripe_one.setValue(0);
		}
	}
}

// Wenn Bewegung "light up" - sobald keine Bewegung "light down"
// Impuls effect
// Mit Motionsensor justierbar
// Mainloop und millis abhängig (nichts muss auf diesen Prozess warten)
void LichtAnSolangeInputImpulsAn()
{

	Logging_one.writeLog("Call - LichtAnSolangeInputImpulsAn", extremedebug);

	if (Motionsensor_one.getValue(Logging_one) == true)
	{
		if (LightStripe_one.getValue() != 255)
		{
			if (LightStripe_one.getValue() <= 255)
			{
				lightcounter++;
				LightStripe_one.setValue(lightcounter);
				Logging_one.writeLog("Licht an - " + String(lightcounter), debug);
			}
		}
	}
	else
	{
		if (LightStripe_one.getValue() != 0)
		{
			if (LightStripe_one.getValue() >= 0)
			{
				lightcounter--;
				LightStripe_one.setValue(lightcounter);
				Logging_one.writeLog("Licht an - " + String(lightcounter), debug);
			}
		}
	}
}

// Wenn Bewegung "light up" bis volle Stärke - erst danach "light off"
// NICHT mit Motionsensor justierbar
// Mainloop und millis abhängig (nichts muss auf diesen Prozess warten)
void LichtAnSolangeInputImpulsAn_AusErlaubtNach255()
{
	Logging_one.writeLog("Call - LichtAnSolangeInputImpulsAn_AusErlaubtNach255", extremedebug);

		if (LightStripe_one.getValue() != 255 && lightdoggle == 0)
		{
			if (LightStripe_one.getValue() <= 255 && Motionsensor_one.getValue(Logging_one) == true)
			{
				lightcounter++;
				LightStripe_one.setValue(lightcounter);
				lightdoggle = 0;
				lightswitch = 0;
				Logging_one.writeLog("Licht an - " + String(lightcounter), debug);
			}
			else if (lightcounter <= 255 && Motionsensor_one.getValue(Logging_one) == false)
			{
				LightStripe_one.setValue(lightcounter);
				if (lightswitch == 0) { lightcounter++;}
				Logging_one.writeLog("Licht an - " + String(lightcounter), debug);
			}
		}
		else
		{
			lightdoggle = 1;
		}

		if (LightStripe_one.getValue() != 0 && lightdoggle == 1 && Motionsensor_one.getValue(Logging_one) == false)
		{
			if (LightStripe_one.getValue() > 0)
			{
				lightcounter--;
				LightStripe_one.setValue(lightcounter);
				lightdoggle = 1;
				lightswitch = 1;
				Logging_one.writeLog("Licht aus - " + String(lightcounter), debug);
			}
		}
		else
		{
			lightdoggle = 0;
		}
}

void motionCheck()
{
	Logging_one.writeLog("Call - motionCheck", extremedebug);
	LichtAnSolangeInputImpulsAn();
}

void dhtCheck()
{
	Logging_one.writeLog("Call - dhtCheck", extremedebug);
	float hum = DHTSensor_one.getHumValueOnlyIfChanged(Logging_one);
	float temp = DHTSensor_one.getTempValueOnlyIfChanged(Logging_one);

	if (			  temp	<= 20 && hum <= 50)	{ LED_TempColor("arctic");	Logging_one.writeLog("Set color 'arctic'", debug); }
	if (temp >	20 && temp	<= 23 && hum <= 50) { LED_TempColor("blue");	Logging_one.writeLog("Set color 'blue'", debug); }
	if (temp >	23 && temp	<= 25 && hum >	55)	{ LED_TempColor("green");	Logging_one.writeLog("Set color 'green'", debug); }
	if (temp >	25 && temp	<= 27 && hum >= 60) { LED_TempColor("yellow");  Logging_one.writeLog("Set color 'yellow'", debug); }
	if (temp >	27 && temp	<= 30 && hum >= 70) { LED_TempColor("orange");  Logging_one.writeLog("Set color 'orange'", debug); }
	if (temp >	30				  && hum >= 80) { LED_TempColor("red");		Logging_one.writeLog("Set color 'red'", debug); }
}

	//*******************************************************
	//************************ SETUP ************************
	//*******************************************************
void setup()
{

	Logging_one.writeLog("Setup Begin", debug);
	neopixelobjekt(255, Logging_one);
	Logging_one.writeLog("Setup End", debug);
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