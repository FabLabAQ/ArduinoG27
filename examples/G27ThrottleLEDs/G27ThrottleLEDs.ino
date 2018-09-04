#include "ArduinoG27.h"

ArduinoG27 G27;

void setup()
{
	G27.Init();
}

void loop()
{
	G27.Task();
	static uint32_t OldMillis;
	if(millis() > OldMillis+20) {
		uint8_t Throttle = G27.GetThrottle();
		uint8_t LEDs = ~(0xFF << (Throttle >> 5));
		G27.SetLEDs(LEDs);
		OldMillis = millis();
	}
}