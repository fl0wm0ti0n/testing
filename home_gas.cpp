// 
// 
// 

#include "home_gas.h"

home_gas::home_gas(String n, int p)
	:home_sensor(t_sensor_type::analogIn_sens, n, p)
{
	home_sensor::getValue(analogRead(p));
	setPin(p);
}

home_gas::~home_gas()
= default;

int home_gas::setPin(int iPin)
{
	iPinNum = iPin;
	pinMode(iPinNum, INPUT);
}

int home_gas::getRawValue()
{
	iAnalogValue = analogRead(iPinNum);
	return iAnalogValue;
}

float home_gas::getCO2Value()
{
	sensorValue = getRawValue();
	sensorResistance = (1023. / (float)sensorValue * 5. - 1.)*RLOAD;

	value = PARA * pow(sensorResistance / RZERO, -PARB);
	return value;
}

float home_gas::getCOValue()
{
	sensorValue = getRawValue();

	v_out = (float)sensorValue * (v_in / 1023.0);
	vRatio = (v_in - v_out) / v_out;
	sensorResistance = R_Load * vRatio;
	value = (float)(coefficient_A * pow(vRatio, coefficient_B));

	return value;
}