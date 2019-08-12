
// @file           home_actor.cpp
// @author         flow@p0cki.at
// @date           01.2017
// @brief          baseclass of all actors

#include "home_actor.h"
#include "home_constants.h"

home_actor::home_actor(t_actor_type t, String n, int p)
	:m_iType(t), m_cName(n), m_iValue(0), m_iPin(p)
{
	pinMode(m_iPin, OUTPUT);
}

home_actor::~home_actor()
{

}

bool home_actor::setValue(int v)
{
	m_iValue = v;
	return true;
}

