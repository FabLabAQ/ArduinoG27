#include "ArduinoG27.h"

ArduinoG27 G27;

void setup()
{
	Serial.begin(115200);
	G27.Init();

	Serial.println(F("Initializing, please wait.\nEnjoy the LED show while waiting!"));

	const uint8_t LEDs[] = {
			ArduinoG27::SET_LEDS_GREEN_1,
			ArduinoG27::SET_LEDS_GREEN_2,
			ArduinoG27::SET_LEDS_YELLOW_1,
			ArduinoG27::SET_LEDS_YELLOW_2,
			ArduinoG27::SET_LEDS_RED,
			ArduinoG27::SET_LEDS_YELLOW_2,
			ArduinoG27::SET_LEDS_YELLOW_1,
			ArduinoG27::SET_LEDS_GREEN_2,
			ArduinoG27::SET_LEDS_GREEN_1,
			ArduinoG27::SET_LEDS_NONE,
			ArduinoG27::SET_LEDS_GREEN_1,
			ArduinoG27::SET_LEDS_GREEN_1 | ArduinoG27::SET_LEDS_GREEN_2,
			ArduinoG27::SET_LEDS_GREEN_1 | ArduinoG27::SET_LEDS_GREEN_2 | ArduinoG27::SET_LEDS_YELLOW_1,
			ArduinoG27::SET_LEDS_GREEN_1 | ArduinoG27::SET_LEDS_GREEN_2 | ArduinoG27::SET_LEDS_YELLOW_1 | ArduinoG27::SET_LEDS_YELLOW_2,
			ArduinoG27::SET_LEDS_GREEN_1 | ArduinoG27::SET_LEDS_GREEN_2 | ArduinoG27::SET_LEDS_YELLOW_1 | ArduinoG27::SET_LEDS_YELLOW_2 | ArduinoG27::SET_LEDS_RED,
			ArduinoG27::SET_LEDS_GREEN_1 | ArduinoG27::SET_LEDS_GREEN_2 | ArduinoG27::SET_LEDS_YELLOW_1 | ArduinoG27::SET_LEDS_YELLOW_2,
			ArduinoG27::SET_LEDS_GREEN_1 | ArduinoG27::SET_LEDS_GREEN_2 | ArduinoG27::SET_LEDS_YELLOW_1,
			ArduinoG27::SET_LEDS_GREEN_1 | ArduinoG27::SET_LEDS_GREEN_2,
			ArduinoG27::SET_LEDS_GREEN_1,
			ArduinoG27::SET_LEDS_NONE
	};

	for(uint8_t i = 0; i <= sizeof(LEDs); i++) {
		G27.SetLEDs(LEDs[i]);
		Serial.print(".");
		uint32_t EndTime = millis() + 250;
		while (millis() < EndTime)
			G27.Task();
	}

	Serial.println(F("\nInit done.\n\nAvailable commands (not case-sensitive):"
			"\n\tSetWheelRange(range[from 270 to 900])"
			"\n\tSetWheelAutoCenter(Strength [optional from -1 (off) to 15, default 7], StrengthRisingRate [optional from 0 to 255 (default)])"
			"\n\tSetWheelConstantForce(Force [from -128 (off) to 127])"
			"\n\tSetWheelFriction(Friction [from 0 (off) to 15], RightFriction [optional from 0 (off) to 15])"
			"\n\tDisableWheelEffects(Slot [optional from 0 (default) to 4])"
			"\nExamples: SetWheelFriction(15,15) or SetWheelAutoCenter(-1) or DisableWheelEffects()"
			"\n--- IMPORTANT: USE NO LINE END IN THE SERIAL TERMINAL! ---\n"));

}

inline void echoAll() {
	while(Serial.available()) {
		char c = Serial.read();
		Serial.print(c);
	}
}

inline void echo() {
	char c = Serial.read();
	Serial.print(c);
}

void loop()
{
	G27.Task();
	if(Serial.available() > 14) {

		String command = Serial.readStringUntil('(');
		Serial.print(command+'(');

		if(command.equalsIgnoreCase(F("SetWheelRange"))) {
			uint16_t Range = Serial.parseInt();
			Serial.print(Range);
			G27.SetWheelRange(Range);
		}

		else if(command.equalsIgnoreCase(F("SetWheelAutoCenter"))) {
			if(Serial.available() > 1) {
				int8_t Strength = Serial.parseInt();
				Serial.print(Strength);
				if(Serial.available() > 1) {
					echo();
					uint8_t StrengthRisingRate = Serial.parseInt();
					Serial.print(StrengthRisingRate);
					G27.SetWheelAutoCenter(Strength, StrengthRisingRate);
				}
				else G27.SetWheelAutoCenter(Strength);
			}
			else G27.SetWheelAutoCenter();
		}

		else if(command.equalsIgnoreCase(F("SetWheelConstantForce"))) {
			int8_t Force = Serial.parseInt();
			Serial.print(Force);
			G27.SetWheelConstantForce(Force);
		}

		else if(command.equalsIgnoreCase(F("SetWheelFriction"))) {
			uint8_t Friction = Serial.parseInt();
			Serial.print(Friction);
			if(Serial.available() > 1) {
				echo();
				uint8_t RightFriction = Serial.parseInt();
				Serial.print(RightFriction);
				G27.SetWheelFriction(Friction, RightFriction);
			}
			else G27.SetWheelFriction(Friction);
		}

		else if(command.equalsIgnoreCase(F("DisableWheelEffects"))) {
			if(Serial.available() > 1) {
				uint8_t Slot = Serial.parseInt();
				Serial.print(Slot);
				G27.DisableWheelEffects(Slot);
			}
			else G27.DisableWheelEffects();
		}

		else echoAll();

		echoAll();
		Serial.println();
	}
}
