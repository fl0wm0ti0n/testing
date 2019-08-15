// @file           home_log.cpp
// @author         flow@p0cki.at
// @date           08.2019
// @brief          baseclass of logging

#include "home_log.h"
#include "Streaming.h"
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

	aEnumlvl[0] = "error";
	aEnumlvl[1] = "warni";
	aEnumlvl[2] = "senso";
	aEnumlvl[3] = "debug";
	aEnumlvl[4] = "exdeb";
}

home_log::~home_log()
{
		// Report number of errors and warnings
		/*Serial << "---------------------------------------------------" << endl;
		Serial << iNumErrors << " errors" << endl;
		Serial << iNumWarnings << " warnings" << endl;
		Serial << iNumSensors << " sensormeasurments" << endl;
		Serial << iNumDebugs << " debuginfos" << endl;
		Serial << iNumExtremedebugs << " extremedebuginfos" << endl;
		Serial << "----------------------Logende----------------------";*/
}

void home_log::writeLog(String text, t_log_level llevel)
{
	/*if (llevel = error) { iNumErrors++; }
	if (llevel = warning) { iNumWarnings++; }
	if (llevel = sensordata) { iNumSensors++; }
	if (llevel = debug) { iNumDebugs++; }
	if (llevel = extremedebug) { iNumExtremedebugs++; }*/

	handleLog(getActualTimestamp(), text, llevel);
}

String home_log::getActualTimestamp()
{
	iSekunde = millis() / 1000;
	if (iSekunde >= 3600)
	{
		iStunde = 0;
		while (iSekunde >= 3600)
		{
			iStunde++;
			iSekunde = iSekunde - 3600;
		}
	}

	if (iSekunde >= 60)
	{
		iMinute = 0;
		while (iSekunde >= 60)
		{
			iMinute++;
			iSekunde = iSekunde - 60;
		}
	}

	sStunde = String(iStunde);
	sMinute = String(iMinute);
	sSekunde = String(iSekunde);

	if (sStunde.length()	== 1) { sStunde		= "0" + sStunde; }
	if (sMinute.length()	== 1) { sMinute		= "0" + sMinute; }
	if (sSekunde.length()	== 1) { sSekunde	= "0" + sSekunde; }

	sTimestamp = sStunde + ":" + sMinute + ":" + sSekunde;

	return sTimestamp;
}

String home_log::getLogArchive(t_log_level llevel)
{
	String output;

	if (m_iLogTarget_ == archive)
	{
		if (m_iLogLvl_ = llevel)
		{
			output = "Funktion wurde noch nicht implementiert und benötigt ein Hardwaremodul";
		}
	}
	else
	{
		output = "Das Archivieren der Protokolle ist deaktiviert";
	}
	
	return output;
}

void home_log::handleLog(String time, String text, t_log_level llevel)
{

	/*
		error = 0,
		warni = 1,
		senso = 2,
		debug = 3,
		exdeb = 4,
	*/

	if (m_iLogLvl_ >= llevel)
	{
		switch (m_iLogTarget_)
		{
		case 0:
			Serial << time << " : " << aEnumlvl[llevel] << " : " << text << endl;
			break;
		case 1:
			// Netzwerk Stream?
			break;
		case 2:
			// Archivdata?
			break;
		default:
			Serial << time << " : " << aEnumlvl[llevel] << " : " << text << endl;
			break;
		}
	}

	/*if (m_iLogLvl_ == NULL || llevel == NULL)
	{
		switch (m_iLogTarget_)
		{
		case 0:
			Serial.print(time);
			Serial.print(" :   ");
			Serial.println("Fehler beim Pruefen des Loglevels");
			break;
		case 1:
			// Netzwerk Stream?
			break;
		case 2:
			// Archivdata?
			break;
		default:
			Serial.print(time);
			Serial.print(" :   ");
			Serial.println("Fehler beim Pruefen des LogTargets");
			break;
		}
	}*/
}