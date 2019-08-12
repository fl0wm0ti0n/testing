// @file           home_log.cpp
// @author         flow@p0cki.at
// @date           08.2019
// @brief          baseclass of logging

#include "home_log.h"
#include <time.h>

home_log::home_log(t_log_level t, t_log_target g, String n)
	:m_iLogLvl_(t), m_iLogTarget_(g), m_cName_(n)
{
	switch (m_iLogTarget_)
	{
	case 0:
		Serial.begin(9600);
			break;
	case 1:
		 // Netzwerk init
		break;
	case 2:
		// Archiv init
		break;
	default:
		break;
	}
}

home_log::~home_log()
{
}

void home_log::writeLog(String text, t_log_level llevel)
{
	handleLog(text, llevel);
}

String home_log::getLogArchive(String text, t_log_level llevel)
{
	return String();
}

void home_log::handleLog(String text, t_log_level llevel)
{

	if (m_iLogLvl_ >= llevel)
	{
		switch (m_iLogTarget_)
		{
		case 0:
			Serial.println(text);
			break;
		case 1:
			// Netzwerk Stream?
			break;
		case 2:
			// Archivdata?
			break;
		default:
			Serial.println(text);
			break;
		}
	}
	else
	{
		switch (m_iLogTarget_)
		{
		case 0:
			Serial.println("Fehler beim Prüfen des Loglevels");
			break;
		case 1:
			// Netzwerk Stream?
			break;
		case 2:
			// Archivdata?
			break;
		default:
			Serial.println("Fehler beim Prüfen des LogTargets");
			break;
		}
	}
}