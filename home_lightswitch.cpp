#include "home_lightswitch.h"
#include "home_aout.h"
#include "home_motion.h"
#include "home_constants.h"


home_lightswitch::home_lightswitch(home_aout lightin, home_motion motionin)
{
	light_ = lightin;
	motion_ = motionin;
	i_switch_ = 0;
	i_analog_value_ = 0;
}

home_lightswitch::~home_lightswitch()
= default;

bool home_lightswitch::SwitchLight()
{

	while (true)
	{
		Serial.println("Schleife");
		if (motion_.getValue(PIN_MOTION_1) == true)
		{
			if (light_.getValue() != 255)
			{
				Serial.println("On");
				for (int i = 1; i <= 255; ++i)
				{
					light_.setValue(i);
					delay(DELAY_LIGHT_UP);
				}
				light_.setValue(255);
			}
		}
		else
		{
			if (light_.getValue() != 0)
			{
				Serial.println("Off");
				for (int j = 255; j >= 0; --j)
				{
					light_.setValue(j);
					delay(DELAY_LIGHT_DOWN);
				}
				light_.setValue(0);
			}
		}
	}
}