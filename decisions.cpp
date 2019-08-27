#include "decisions.h"

decisions::decisions(t_decision_type t, String n)
	:m_iType(t), m_cName(n)
{
}

decisions::~decisions()
= default;

// Wenn Bewegung "light up" bis das Licht ganz an ist nach einer am Motionsensor eingestellten Zeit geht das licht wieder aus.
// Mainloop und millis unabhängig (alles muss auf diesen Prozess warten)
/*int decisions::LichtKomplettSchalten_SobaldImpuls(bool o_sensor, int o_actor, logger &Logging_one)
{
	Logging_one.writeLog("Call - LichtKomplettSchalten_SobaldImpuls", extremedebug);

	if (o_sensor == true)
	{
		if (o_actor != 255)
		{
			for (int i = 0; i <= 255; ++i)
			{
				LightStripe_one.setValue(i, Logging_one);
				delay(DEFAULT_LIGHTFDELAY);
				Logging_one.writeLog("Licht an - " + String(LightStripe_one.getValue()), debug);
			}
			LightStripe_one.setValue(255, Logging_one);
		}
	}
	else
	{
		if (LightStripe_one.getValue() != 0)
		{

			for (int j = 255; j >= 0; --j)
			{
				LightStripe_one.setValue(j, Logging_one);
				delay(DEFAULT_LIGHTFDELAY);
				Logging_one.writeLog("Licht aus - " + String(LightStripe_one.getValue()), debug);
			}
			LightStripe_one.setValue(0, Logging_one);
		}
	}
	return lightcounter;
}*/

// Wenn Bewegung "light up" - sobald keine Bewegung "light down"
// Impuls effect
// Mit Motionsensor justierbar
// Mainloop und millis abhängig (nichts muss auf diesen Prozess warten)
int decisions::LichtAnSolangeInputImpulsAn(bool o_sensor, int o_actor, logger &Logging_one)
{
	Logging_one.writeLog("Call - LichtAnSolangeInputImpulsAn", extremedebug);

	if (o_sensor == true)
	{
		if (lightcounter != 255)
		{
			if (lightcounter <= 255)
			{
				lightcounter++;
				Logging_one.writeLog("Licht an - " + String(lightcounter), debug);
			}
		}
	}
	else
	{
		if (lightcounter != 0)
		{
			if (lightcounter >= 0)
			{
				lightcounter--;
				Logging_one.writeLog("Licht aus - " + String(lightcounter), debug);
			}
		}
	}
	return lightcounter;
}

// Wenn Bewegung "light up" bis volle Stärke - erst danach "light off"
// NICHT mit Motionsensor justierbar
// Mainloop und millis abhängig (nichts muss auf diesen Prozess warten)
/*int decisions::LqichtAnSolangeInputImpulsAn_AusErlaubtNach255(bool o_sensor, int o_actor, logger &Logging_one)
{
	Logging_one.writeLog("Call - LichtAnSolangeInputImpulsAn_AusErlaubtNach255", extremedebug);

	if (LightStripe_one.getValue() != 255 && lightdoggle == 0)
	{
		if (LightStripe_one.getValue() <= 255 && Motionsensor_one.getValue(Logging_one) == true)
		{
			lightcounter++;
			LightStripe_one.setValue(lightcounter, Logging_one);
			lightdoggle = 0;
			lightswitch = 0;
			Logging_one.writeLog("Licht an - " + String(lightcounter), debug);
		}
		else if (lightcounter <= 255 && Motionsensor_one.getValue(Logging_one) == false)
		{
			LightStripe_one.setValue(lightcounter, Logging_one);
			if (lightswitch == 0) { lightcounter++; }
			Logging_one.writeLog("Licht an - " + String(lightcounter), debug);
		}
	}
	else
	{
		lightdoggle = 1;
	}

	if (LightStripe_one.getValue() != 0 && lightdoggle == 1 && Motionsensor_one.getValue(Logging_one) == false)
	{
		if (LightStripe_one.getValue() > 0)
		{
			lightcounter--;
			LightStripe_one.setValue(lightcounter, Logging_one);
			lightdoggle = 1;
			lightswitch = 1;
			Logging_one.writeLog("Licht aus - " + String(lightcounter), debug);
		}
	}
	else
	{
		lightdoggle = 0;
	}
	return lightcounter;
}*/
	/*
	// Wenn Bewegung "light up" bis das Licht ganz an ist nach einer am Motionsensor eingestellten Zeit geht das licht wieder aus.
	// Mainloop und millis unabhängig (alles muss auf diesen Prozess warten)
	void decisions::LichtKomplettSchalten_SobaldImpuls(bool o_sensor, int o_actor, logger &Logging_one)
	{
		Logging_one.writeLog("Call - LichtKomplettSchalten_SobaldImpuls", extremedebug);

		if (Motionsensor_one.getValue(Logging_one) == true)
		{
			if (LightStripe_one.getValue() != 255)
			{
				for (int i = 0; i <= 255; ++i)
				{
					LightStripe_one.setValue(i, Logging_one);
					delay(DEFAULT_LIGHTFDELAY);
					Logging_one.writeLog("Licht an - " + String(LightStripe_one.getValue()), debug);
				}
				LightStripe_one.setValue(255, Logging_one);
			}
		}
		else
		{
			if (LightStripe_one.getValue() != 0)
			{

				for (int j = 255; j >= 0; --j)
				{
					LightStripe_one.setValue(j, Logging_one);
					delay(DEFAULT_LIGHTFDELAY);
					Logging_one.writeLog("Licht aus - " + String(LightStripe_one.getValue()), debug);
				}
				LightStripe_one.setValue(0, Logging_one);
			}
		}
	}

	// Wenn Bewegung "light up" - sobald keine Bewegung "light down"
	// Impuls effect
	// Mit Motionsensor justierbar
	// Mainloop und millis abhängig (nichts muss auf diesen Prozess warten)
	void decisions::LichtAnSolangeInputImpulsAn(sensor o_sensor, actor o_actor, logger &Logging_one)
	{

		Logging_one.writeLog("Call - LichtAnSolangeInputImpulsAn", extremedebug);

		if (Motionsensor_one.getValue(Logging_one) == true)
		{
			if (LightStripe_one.getValue() != 255)
			{
				if (LightStripe_one.getValue() <= 255)
				{
					lightcounter++;
					LightStripe_one.setValue(lightcounter, Logging_one);
					Logging_one.writeLog("Licht an - " + String(lightcounter), debug);
				}
			}
		}
		else
		{
			if (LightStripe_one.getValue() != 0)
			{
				if (LightStripe_one.getValue() >= 0)
				{
					lightcounter--;
					LightStripe_one.setValue(lightcounter, Logging_one);
					Logging_one.writeLog("Licht an - " + String(lightcounter), debug);
				}
			}
		}
	}

	// Wenn Bewegung "light up" bis volle Stärke - erst danach "light off"
	// NICHT mit Motionsensor justierbar
	// Mainloop und millis abhängig (nichts muss auf diesen Prozess warten)
	void decisions::LichtAnSolangeInputImpulsAn_AusErlaubtNach255(sensor o_sensor, actor o_actor, logger &Logging_one)
	{
		Logging_one.writeLog("Call - LichtAnSolangeInputImpulsAn_AusErlaubtNach255", extremedebug);

		if (LightStripe_one.getValue() != 255 && lightdoggle == 0)
		{
			if (LightStripe_one.getValue() <= 255 && Motionsensor_one.getValue(Logging_one) == true)
			{
				lightcounter++;
				LightStripe_one.setValue(lightcounter, Logging_one);
				lightdoggle = 0;
				lightswitch = 0;
				Logging_one.writeLog("Licht an - " + String(lightcounter), debug);
			}
			else if (lightcounter <= 255 && Motionsensor_one.getValue(Logging_one) == false)
			{
				LightStripe_one.setValue(lightcounter, Logging_one);
				if (lightswitch == 0) { lightcounter++; }
				Logging_one.writeLog("Licht an - " + String(lightcounter), debug);
			}
		}
		else
		{
			lightdoggle = 1;
		}

		if (LightStripe_one.getValue() != 0 && lightdoggle == 1 && Motionsensor_one.getValue(Logging_one) == false)
		{
			if (LightStripe_one.getValue() > 0)
			{
				lightcounter--;
				LightStripe_one.setValue(lightcounter, Logging_one);
				lightdoggle = 1;
				lightswitch = 1;
				Logging_one.writeLog("Licht aus - " + String(lightcounter), debug);
			}
		}
		else
		{
			lightdoggle = 0;
		}*/