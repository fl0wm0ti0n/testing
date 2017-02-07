
// 
// 
// 

#include "home_dout.h"

home_dout::home_dout(String n, int p)
	:home_actor(tActorType::digitalOut, n, p)
{
	home_actor::setValue(digitalRead(p));
}

home_dout::~home_dout()
{
}

bool home_dout::setValue(int v)
{
	if (getValue() != v)
	{
		home_actor::setValue(v);
		digitalWrite(getPin(),v);
	}
	return true;
}

bool home_dout::Doggle()
{
	return setValue(!getValue());
}