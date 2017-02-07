
// @file           home_touch.cpp
// @author         flow@p0cki.at
// @date           11.2016
// @brief          touch sensor Values


#include "home_touch.h"
#include "home_constants.h"

home_touch::home_touch()
{
	Serial.println("--touch aufgerufen--");
}

home_touch::~home_touch()
{


}

int home_touch::setPin(int iPin)
{
	iPinNum = iPin;
	pinMode(iPinNum, INPUT);
}

int home_touch::getValue()
{
	iTouchValue = digitalRead(iPinNum);
	Serial.print("digitalRead: ");
	Serial.println(iTouchValue);
	return iTouchValue;
}

int home_touch::getAnalog()
{

}