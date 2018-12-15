// 
// 
// 

#include "DHT.h"
#include "home_dht.h"

home_dht::home_dht(String n, int p)
	:home_sensor(tSensorType::DHT_sens, n, p)
{
	//home_sensor::getValue(digitalRead(p));
	dht.begin();
}

home_dht::~home_dht()
= default;

float home_dht::getTempValue()
{
	//home_sensor::getValue(getPin());

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

float home_dht::getHumValue()
{
	//home_sensor::getValue(getPin());

	temp = dht.readTemperature();
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