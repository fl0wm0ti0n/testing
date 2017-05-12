
// @file           home_sensor.cpp
// @author         flow@p0cki.at
// @date           01.2017
// @brief          baseclass of all sensors

#include "home_sensor.h"
#include "home_constants.h"

home_sensor::home_sensor(tSensorType t, String n, int p)
	:m_iType(t), m_cName(n), m_iValue(0), m_iPin(p)
{
	pinMode(m_iPin, INPUT);
}

home_sensor::~home_sensor()
{

}

bool home_sensor::getValue(int v)
{
	m_iValue = v;
	return true;
}



