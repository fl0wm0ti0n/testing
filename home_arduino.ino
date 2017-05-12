
// @file           home_arduino.ino
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

/*
	//*******************************************************
	//********************* DECLARATION *********************
	//*******************************************************



	//*******************************************************
	//************************ SETUP ************************
	//*******************************************************
	*/
void setup()
{
	Serial.begin(9600);
	home_dout light1("light1", PIN_PWM_2);
	home_motion motion1("motion1", PIN_MOTION_1);

	while (true)
	{
		Serial.println("Schleife");
		if (motion1.getValue(PIN_MOTION_1) == true);
		{
				light1.doggle();
				Serial.println("doggle");
		}
		delay(500);
	}
	
}


	//*******************************************************
	//************************ LOOP *************************
	//*******************************************************
void loop()
{

}

