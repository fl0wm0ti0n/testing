// @file           home_log.h
// @author         flow@p0cki.at
// @date           08.2019
// @brief          baseclass of logging


#ifndef _HOME_LOG_h
#define _HOME_LOG_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

enum t_log_level
{
	error = 0,
	warning = 1,
	sensordata = 2,
	debug = 3,
	extremedebug = 4,
};

enum t_log_target
{
	serial = 0,
	net = 1,
	archive = 2,
};

class home_log
{

private:
	String log_;
	t_log_level m_iLogLvl_;
	t_log_target m_iLogTarget_;
	String m_cName_;
	String logArchive_;
	void handleLog(String text, t_log_level llevel);

public:
	home_log(t_log_level t, t_log_target g, String n);		// Constructor
	virtual ~home_log();									// Destructor

	void writeLog(String text, t_log_level llevel);
	String getLogArchive(String text, t_log_level llevel);


	t_log_level setLoglevel(t_log_level llevel)
	{
		m_iLogLvl_ = llevel;
	}

	t_log_target setLogTarget(t_log_target ltarget)
	{
		m_iLogTarget_ = ltarget;
	}

	t_log_level getLogLevel()
	{
		return m_iLogLvl_;
	}

	t_log_target getLogTarget()
	{
		return m_iLogTarget_;
	}

	String getName()
	{
		return m_cName_;
	}
};

#endif