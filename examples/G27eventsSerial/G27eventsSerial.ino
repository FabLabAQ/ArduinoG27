#include "ArduinoG27events.h"

ArduinoG27events G27;
//ArduinoG27events G27(&Serial);

void setup()
{
	Serial.begin(115200);
	G27.Init();

	G27.SetWheelChangeThreshold(1);
	G27.SetThrottleChangeThreshold(1);
	G27.SetBrakeChangeThreshold(1);
	G27.SetClutchChangeThreshold(1);
	//G27.SetHorizontalShifterChangeThreshold(1);
	//G27.SetVerticalShifterChangeThreshold(1);
}


void loop()
{
	G27.Task();
}
