
// 
// 
// 

#include "analogOut.h"

analogOut::analogOut(String n, int p)
	:actor(digitalOut_act, n, p)
{
	actor::setValue(analogRead(p));
}

analogOut::~analogOut()
{
}

bool analogOut::setValue(int v)
{
	//Serial.begin(9600);
	if (getValue() != v)
	{
		//Serial.println("SetValue");
		actor::setValue(v);
		analogWrite(getPin(), v);
	}
	return true;
}

bool analogOut::doggle()
{
	return setValue(!getValue());
}