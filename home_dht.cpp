// 
// 
// 

#include "DHT.h"
#include "home_dht.h"

home_dht::home_dht(String n, int p)
	:home_sensor(t_sensor_type::DHT_sens, n, p)
{
	dht.begin();
}

home_dht::~home_dht()
= default;

float home_dht::getTempValue()
{
	temp = dht.readTemperature();
		
	Serial.print("Temperatur: ");
	Serial.print(temp);
	Serial.println("°C, ");

	return temp;
}

float home_dht::getHumValue()
{
	hum = dht.readHumidity();

	Serial.print("Feuchtigkeit: ");
	Serial.print(hum);
	Serial.println("%");

	return hum;
}

float home_dht::getTempValueOnlyIfChanged()
{
	temp = dht.readTemperature();

	if (temp != savetemp)
	{
		Serial.print("Temperatur: ");
		Serial.print(temp);
		Serial.println("°C, ");
		savetemp = temp;
	}
	return temp;
}

float home_dht::getHumValueOnlyIfChanged()
{
	hum = dht.readHumidity();

	if (hum != savehum)
	{
		Serial.print("Feuchtigkeit: ");
		Serial.print(hum);
		Serial.println("%");
		savehum = hum;
	}
	return hum;
}