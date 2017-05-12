
// 
// 
// 

#include "home_dout.h"

home_dout::home_dout(String n, int p)
	:home_actor(tActorType::digitalOut_act, n, p)
{
	home_actor::setValue(digitalRead(p));
}

home_dout::~home_dout()
{
}

bool home_dout::setValue(int v)
{
	Serial.begin(9600);
	if (getValue() != v)
	{
		Serial.println("SetValue");
		home_actor::setValue(v);
		digitalWrite(getPin(),v);
	}
	return true;
}

bool home_dout::doggle()
{
	return setValue(!getValue());
}