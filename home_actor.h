
// @file           home_actor.h
// @author         flow@p0cki.at
// @date           01.2017
// @brief          baseclass of all actors

#ifndef _HOME_ACTOR_h
#define _HOME_ACTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum tActorType
{
	undefined_act = 0,
	digitalOut_act = 1,
	AnalogOut_act = 2,
	I2C_act = 3,
	WS2812_act = 4,
	PWM_act = 5,
	RGB_act = 6
};

class home_actor
{
 public:
	 home_actor(tActorType t, String n, int p);
	 virtual ~home_actor();

	 inline tActorType getType()
		{return m_iType;}
	 
	 inline String getName()
		{return m_cName;}
	 
	 inline int getValue()
		{return m_iValue;}

	 inline int getPin()
		{ return m_iPin;}
	
	 virtual bool setValue(int v);

 protected:

 private:
	 tActorType m_iType;
	 String m_cName;
	 int m_iValue;
	 int m_iPin;
};

#endif

