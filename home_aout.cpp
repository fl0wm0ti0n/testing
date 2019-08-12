
// 
// 
// 

#include "home_aout.h"

home_aout::home_aout(String n, int p)
	:home_actor(t_actor_type::digitalOut_act, n, p)
{
	home_actor::setValue(analogRead(p));
}

home_aout::~home_aout()
{
}

bool home_aout::setValue(int v)
{
	//Serial.begin(9600);
	if (getValue() != v)
	{
		//Serial.println("SetValue");
		home_actor::setValue(v);
		analogWrite(getPin(), v);
	}
	return true;
}

bool home_aout::doggle()
{
	return setValue(!getValue());
}