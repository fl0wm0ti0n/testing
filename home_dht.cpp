// 
// 
// 

#include "DHT.h"
#include "home_dht.h"
#include "home_log.h"

home_dht::home_dht(String n, int p)
	:home_sensor(t_sensor_type::DHT_sens, n, p)
{
	dht.begin();
}

home_dht::~home_dht()
= default;

float home_dht::getTempValue(home_log &logging_one)
{
	temp = dht.readTemperature();
	logging_one.writeLog("Die Temperatur betr\u00e4gt " + String(temp) + "C", sensordata);
	return temp;
}

float home_dht::getHumValue(home_log &logging_one)
{
	hum = dht.readHumidity();
	logging_one.writeLog("Die Luftfeuchtigkeit betr\u00e4gt " + String(hum) + "%", sensordata);
	return hum;
}

float home_dht::getTempValueOnlyIfChanged(home_log &logging_one)
{
	temp = dht.readTemperature();
	if (temp != savetemp)
	{
		logging_one.writeLog("Die Temperatur betr\u00e4gt " + String(temp) + "C", sensordata);
		savetemp = temp;
	}
	return temp;
}

float home_dht::getHumValueOnlyIfChanged(home_log &logging_one)
{
	hum = dht.readHumidity();
	if (hum != savehum)
	{
		logging_one.writeLog("Die Luftfeuchtigkeit betr\u00e4gt " + String(hum) + "%", sensordata);
		savehum = hum;
	}
	return hum;
}