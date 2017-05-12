
// @file           home_sensor.h
// @author         flow@p0cki.at
// @date           01.2017
// @brief          baseclass of all sensors

#ifndef _HOME_SENSOR_h
#define _HOME_SENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum tSensorType
{
	undefined_sens = 0,
	digitalIn_sens = 1,
	analogIn_sens = 2,
	I2C_sens = 3

};

class home_sensor
{
public:
	home_sensor(tSensorType t, String n, int p);
	virtual ~home_sensor();

	inline tSensorType getType()
	{return m_iType;}

	inline String getName()
	{return m_cName;}

	//inline int getValue()
	//{return m_iValue;}

	inline int getPin()
	{return m_iPin;}

	virtual bool getValue(int v);

protected:

private:
	tSensorType m_iType;
	String m_cName;
	int m_iValue;
	int m_iPin;
};

#endif


