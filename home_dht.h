// home_dht.h

#ifndef _HOME_DHT_h
#define _HOME_DHT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "home_sensor.h"
//#include <DHT_sensor_library/DHT.h>
#include <DHT.h>

class home_dht :public home_sensor
{
	float temp;
	float hum;
	float savetemp;
	float savehum;
	DHT dht = DHT(getPin(),DHT22);

public:
		home_dht(String n, int p);			// Constructor
		virtual ~home_dht();				// Destructor
		float getTempValue();				// Method: get Value
		float getHumValue();				// Method: get Value
		float getTempValueOnlyIfChanged();	// Method: get Value
		float getHumValueOnlyIfChanged();	// Method: get Value
};

#endif