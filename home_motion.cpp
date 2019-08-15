// 
// 
// 

#include "home_motion.h"
#include "home_constants.h"

home_motion::home_motion(String n, int p)
	:home_sensor(t_sensor_type::digitalIn_sens, n, p)
{
	home_sensor::getValue(digitalRead(p));

}

home_motion::~home_motion()
= default;

bool home_motion::getValue(int v, home_log &logging_one)
{
	home_sensor::getValue(getPin());
	if (digitalRead(getPin()) == LOW && iMotionState != 0)
	{
		iMotionState = 0;
		iMotionValue = false;
		logging_one.writeLog("motion dedected", debug);
	}
	if (digitalRead(getPin()) == HIGH && iMotionState != 1)
	{
		iMotionState = 1;
		iMotionValue = true;
		Serial.println("bewegung erkannt");

	}
		return iMotionValue;
}