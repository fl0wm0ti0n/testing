
#define TOUCH_DATA_PIN	2								// Pin for capactitive touch sensor



//*******************************************************
//************************ SETUP ************************
//*******************************************************
void setup()
{

//********************** Touchy ************************
	Serial.begin(9600);									// USB baud rate
	pinMode(TOUCH_DATA_PIN, INPUT);						//setze Datenpin als Input
}


//*******************************************************
//************************ LOOP *************************
//*******************************************************
void loop()
{
	bool flip = false;

//********************** Touchy ************************
	int ctsValue = digitalRead(TOUCH_DATA_PIN);			// lese Datenpin aus

	if (ctsValue == HIGH)
	{
		flip = !flip;									// wert wird invertiert
	}

	if (flip == true)
	{
		LED_WS2812(1);									// LED ansteuerung
		Serial.println("touched");						// schreibe über usb aus
	}
	else
	{
		LED_WS2812(0);									// LED ansteuerung
		Serial.println("not touched");					// schreibe über usb aus
	}
	delay(500);

}