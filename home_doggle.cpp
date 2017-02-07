
// @file           home_doggle.cpp
// @author         flow@p0cki.at
// @date           12.2016
// @brief          flip a Value

#include "home_doggle.h"
#include "home_constants.h"

int home_doggle::iflip = false;
int home_doggle::iflop = false;

home_doggle::home_doggle()
{
	Serial.println("--doggle aufgerufen--");
	iReturnValue = false;
}

home_doggle::~home_doggle()
{

}

int home_doggle::flip(int iValue)
{

	Serial.print("iflip: ");
	Serial.println(iflip);
	Serial.print("iflop: ");
	Serial.println(iflop);

	//********************** routine ************************
	if (iValue == HIGH)
	{
		Serial.println("Touch: HIGH");

		if (!iflop)
		{
			iflop = true;
			Serial.println(iflip);
			iflip = !iflip;

			if (iflip)
			{
				iReturnValue = true;
				Serial.println("doggle: On");
			}
			else
			{
				iReturnValue = false;
				Serial.println("doggle: Off");
			}
		}

	}
	else
	{
		iflop = false;
		Serial.println("Touch: LOW");
	}

	return iReturnValue;
}