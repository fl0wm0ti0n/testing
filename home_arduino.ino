// @file           home_arduino.ino
// @author         flow@p0cki.net
// @date           12.2016
// @brief          main routine

#include "FastLED.h"
#include <DHT.h>
#include "motionSensor.h"
#include "constants.h"
#include "analogOut.h"
#include "dhtSensor.h"
#include "randomtemplight.h"
#include "gasSensor.h"
#include "logger.h"
#include "decisions.h"

//*******************************************************
//********************* DECLARATION *********************
//*******************************************************

// Objekte welche sofort benötigt werden.
logger Logging_one(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, "Logging1");
analogOut LightStripe_one("lightstripe 1", PIN_PWM_2);
motionSensor Motionsensor_one("motionsensor 1", PIN_MOTION_1);
dhtSensor DHTSensor_one("dhtsensor 1", PIN_HUM_1);
decisions LightUpStripe(lightOn,"LichtAnAus");
//gasSensor gasSensor("gassensor 1 - MQ135", PIN_GAS_MQ135_1);
//gasSensor gasSensor2("gassensor 2 - MQ7", PIN_GAS_MQ7_1);

// Variablen deklarieren in denen die Startzeiten
// der einzelnen Zeitfunktionen gespeichert werden
unsigned long startzeit_1 = 0;
unsigned long startzeit_2 = 0;
unsigned long startzeit_3 = 0;
unsigned long startzeit_4 = 0;
unsigned long startzeit_5 = 0;

void motionCheck()
{
	Logging_one.writeLog("Call - motionCheck", debug);
	LightStripe_one.setValue((LightUpStripe.LichtAnSolangeInputImpulsAn(Motionsensor_one.getValue(Logging_one), LightStripe_one.getValue(), Logging_one)), Logging_one);
}

void dhtCheck()
{
	Logging_one.writeLog("Call - dhtCheck", debug);
	float hum = DHTSensor_one.getHumValueOnlyIfChanged(Logging_one);
	float temp = DHTSensor_one.getTempValueOnlyIfChanged(Logging_one);
	WS2812_FadeToTargetColor(temp, hum, Logging_one);
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
	// Alle 20 Millisekunden wird der Bewegungsmelder geprüft.
	if (millis() - startzeit_1 >= laufzeit_20)
	{
		startzeit_1 = millis();
		motionCheck();
	}

	// Alle 500 Millisekunden wird der DHT-Sensor geprüft.
	if (millis() - startzeit_2 >= laufzeit_500)
	{
		startzeit_2 = millis();
		dhtCheck();
	}
}