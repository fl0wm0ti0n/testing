// @file           home_arduino.ino
// @author         flow@p0cki.at
// @date           12.2016
// @brief          main routine

#include <DHT.h>
#include <FastLED.h>
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


//*******************************************************
//********************* DECLARATION *********************
//*******************************************************

home_aout lightStripe("lightstripe 1", PIN_PWM_1);
home_motion motionSensor("motionsensor 1", PIN_MOTION_1);
home_dht dhtSensor("dhtsensor 1", PIN_HUM_1);
home_ain gasSensor("gassensor 1 - MQ135", PIN_GAS_MQ135_1);
home_ain gasSensor2("gassensor 2 - MQ7", PIN_GAS_MQ7_1);

// Variablen deklarieren in denen die Startzeiten
// der einzelnen Zeitfunktionen gespeichert werden
unsigned long startzeit_1 = 0;
unsigned long startzeit_2 = 0;
unsigned long startzeit_3 = 0;
unsigned long startzeit_4 = 0;
unsigned long startzeit_5 = 0;

// Definitionen der einzelnen Schaltzeiten
#define        laufzeit_500		500UL
#define        laufzeit_1k		1000UL
#define        laufzeit_1k5		1500UL
#define        laufzeit_2k		2000UL
#define        laufzeit_5k		5000UL


void motionCheck()
{
	if (motionSensor.getValue(PIN_MOTION_1) == true)
	{
		if (lightStripe.getValue() != 255)
		{
			Serial.println("On");
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
			for (int j = 255; j >= 0; --j)
			{
				lightStripe.setValue(j);
				delay(20);
			}
			lightStripe.setValue(0);
		}
	}
}

void dhtCheck()
{
	if (dhtSensor.getHumValue() <= 40) { LED_TempColor("arctic"); }
	if (dhtSensor.getTempValue() <= 20 && dhtSensor.getHumValue() <= 50) { LED_TempColor("blue"); }
	if (dhtSensor.getTempValue() > 20 && dhtSensor.getTempValue() <= 23 && dhtSensor.getHumValue() > 50) { LED_TempColor("green"); }
	if (dhtSensor.getTempValue() > 23 && dhtSensor.getTempValue() <= 25 && dhtSensor.getHumValue() >= 60) { LED_TempColor("yellow"); }
	if (dhtSensor.getTempValue() > 25 && dhtSensor.getTempValue() <= 27 && dhtSensor.getHumValue() >= 70) { LED_TempColor("orange"); }
	if (dhtSensor.getTempValue() > 27 && dhtSensor.getHumValue() >= 80) { LED_TempColor("red"); }
}

void GasCheckCO2(home_ain sensor)
{
	float value;
	float sensorValue;
	float resistance;

	#define RLOAD 10.0
	#define RZERO 76.63
	#define PARA 116.6020682
	#define PARB 2.769034857

	sensorValue = sensor.getValue();
	resistance = (1023. / (float)sensorValue * 5. - 1.)*RLOAD;

	value = PARA * pow(resistance / RZERO, -PARB);

	Serial.print(sensor.getName());
	Serial.print(": ");
	Serial.println(value);
}

void GasCheckCO(home_ain sensor)
{

	float vRatio = 0;
	float sensorValue = 0;
	float ppm = 0;
	int v_in = 5;
	float v_out;
	float sensorResistance = 0;

	sensorValue = sensor.getValue();

	#define coefficient_A 19.32
	#define coefficient_B -0.64

	//Load resistance 10 Kohms on the sensor potentiometer
	#define R_Load 10.0

	v_out = (float)sensorValue * (v_in / 1023.0);
	vRatio = (v_in - v_out) / v_out;
	sensorResistance = R_Load * vRatio;
	ppm = (float)(coefficient_A * pow(vRatio, coefficient_B));

	Serial.print(sensor.getName());
	Serial.print(": ");
	Serial.println(ppm);
}

	//*******************************************************
	//************************ SETUP ************************
	//*******************************************************
void setup()
{
	Serial.begin(9600);
	Serial.println("Setup begin");

	//neopixelobjekt(255);

	Serial.println("Setup end");
}

	//*******************************************************
	//************************ LOOP *************************
	//*******************************************************
void loop()
{
	// laufzeit_1 EIN, laufzeit_1 AUS - LED schalten in loop - Schaltzeiten in Millisekunden
	//if (millis() - startzeit_1 >= laufzeit_1k) 
	//{
	//	startzeit_1 = millis();
		motionCheck();
		delay(500);
	//}

	/*if (millis() - startzeit_1 >= laufzeit_5k)
	{
		startzeit_1 = millis();
		dhtCheck();
	}*/

	//GasCheckCO(gasSensor2);
	//GasCheckCO2(gasSensor)
}