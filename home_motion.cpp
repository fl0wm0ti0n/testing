// 
// 
// 

#include "home_motion.h"
#include "home_constants.h"

home_motion::home_motion()
{
	Serial.println("--motion aufgerufen--");
}

home_motion::~home_motion()
{


}

int home_motion::setPin(int iPin)
{
	iPinNum = iPin;
	pinMode(iPinNum, INPUT);
}

int home_motion::getValue()
{

		// Motion dedection only if status changes
		if (digitalRead(iPinNum) == LOW && iMotionState != 0)
		{
			iMotionValue = 0;
			Serial.println("keine bewegung erkannt");
			iMotionState = 0;
		}
		if (digitalRead(iPinNum) == HIGH && iMotionState != 1)
		{
			iMotionValue = 1;
			Serial.println("bewegung erkannt");
			iMotionState = 1;
		}

	return iMotionValue;
}

int home_motion::getAnalog()
{

}