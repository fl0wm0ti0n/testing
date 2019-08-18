// 
// 
// 

#include "DHT.h"
#include "dhtSensor.h"
#include "logger.h"

dhtSensor::dhtSensor(String n, int p)
	:sensor(t_sensor_type::DHT_sens, n, p)
{
	dht.begin();
}

dhtSensor::~dhtSensor()
= default;

float dhtSensor::getTempValue(logger &logging_one)
{
	temp = dht.readTemperature();
	logging_one.writeLog("Die Temperatur betr\u00e4gt " + String(temp) + "C", sensordata);
	return temp;
}

float dhtSensor::getHumValue(logger &logging_one)
{
	hum = dht.readHumidity();
	logging_one.writeLog("Die Luftfeuchtigkeit betr\u00e4gt " + String(hum) + "%", sensordata);
	return hum;
}

float dhtSensor::getTempValueOnlyIfChanged(logger &logging_one)
{
	temp = dht.readTemperature();
	if (temp != savetemp)
	{
		logging_one.writeLog("Die Temperatur betr\u00e4gt " + String(temp) + "C", sensordata);
		savetemp = temp;
	}
	return temp;
}

float dhtSensor::getHumValueOnlyIfChanged(logger &logging_one)
{
	hum = dht.readHumidity();
	if (hum != savehum)
	{
		logging_one.writeLog("Die Luftfeuchtigkeit betr\u00e4gt " + String(hum) + "%", sensordata);
		savehum = hum;
	}
	return hum;
}