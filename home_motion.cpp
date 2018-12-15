// 
// 
// 

#include "home_motion.h"
#include "home_constants.h"

home_motion::home_motion(String n, int p)
	:home_sensor(tSensorType::digitalIn_sens, n, p)
{
	home_sensor::getValue(digitalRead(p));

}

home_motion::~home_motion()
{


}

bool home_motion::getValue(int v)
{
	home_sensor::getValue(getPin());
	if (digitalRead(getPin()) == LOW && iMotionState != 0)
	{
		iMotionState = 0;
		iMotionValue = false;
		Serial.println("keine bewegung erkannt");

	}
	if (digitalRead(getPin()) == HIGH && iMotionState != 1)
	{
		iMotionState = 1;
		iMotionValue = true;
		Serial.println("bewegung erkannt");

	}
		return iMotionValue;
}
