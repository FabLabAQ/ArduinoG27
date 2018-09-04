#include "ArduinoG27events.h"

ArduinoG27events G27;

void setup()
{
	Serial.begin(115200);
	G27.Init();
}


void loop()
{
	G27.Task();
}
