// @file      sensor.h
// @author    flow@p0cki.net
// @date      01.2017
// @brief     baseclass of all sensors

#ifndef _HOME_SENSOR_h
#define _HOME_SENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "logger.h"

enum t_sensor_type
{
	undefined_sens = 0,
	digitalIn_sens = 1,
	analogIn_sens = 2,
	I2C_sens = 3,
	DHT_sens = 4,
	gas_sens = 5
};

class sensor
{

private:
	t_sensor_type m_iType;
	String m_cName;
	int m_iValue;
	int m_iPin;

public:
	sensor(t_sensor_type t, String n, int p);
	virtual ~sensor();

	t_sensor_type getType()
	{return m_iType;}

	String getName()
	{return m_cName;}

	int setPin(int p)
	{
		m_iPin = p;
		pinMode(m_iPin, INPUT);
		return true;
	}

	int getPin()
	{return m_iPin;}

	virtual bool getValue(int v);
};
#endif