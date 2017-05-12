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
	int iMotionState = 0;
	int iMotionValue = 0;
	Serial.begin(9600);
	Serial.println("GetValue");
	if (getValue(getPin()) != v)
	{

		home_sensor::getValue(getPin());
		if (digitalRead(getPin()) == LOW && iMotionState != 0)
		{
			iMotionValue = 0;
			Serial.println("keine bewegung erkannt");
			iMotionState = 0;
		}
		if (digitalRead(getPin()) == HIGH && iMotionState != 1)
		{
			iMotionValue = 1;
			Serial.println("bewegung erkannt");
			iMotionState = 1;
		}

		if (iMotionValue = 1)
		{
			return true;
		}
	}

}
