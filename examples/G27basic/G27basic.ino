#include "ArduinoG27.h"

ArduinoG27 G27;

void setup()
{
	Serial.begin(115200);
	G27.Init();
}

#define ANDPRINT(a, b) if(a & b) Serial.println(F(#b));
#define IFPRINT(a, b) if(a == b) Serial.println(F(#b));
#define NAMEPRINT(x, a) if(x != a) { Serial.print(F(#a": ")); Serial.println(a); x = a; }

void loop()
{
	G27.Task();

	uint8_t HatSwitch = G27.GetHatSwitch();
	static uint8_t OldHatSwitch;
	if(OldHatSwitch != HatSwitch) {
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_IDLE)
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_UP)
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_DOWN)
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_LEFT)
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_RIGHT)
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_UP_RIGHT)
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_DOWN_RIGHT)
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_UP_LEFT)
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_DOWN_LEFT)
		OldHatSwitch = HatSwitch;
	}

	uint8_t ShifterBlackButtons = G27.GetShifterBlackButtons();
	static uint8_t OldShifterBlackButtons;
	if(OldShifterBlackButtons != ShifterBlackButtons) {
		IFPRINT(ShifterBlackButtons, ArduinoG27::SHIFTER_BLACK_BUTTON_IDLE)
		ANDPRINT(ShifterBlackButtons, ArduinoG27::SHIFTER_BLACK_BUTTON_UP)
		ANDPRINT(ShifterBlackButtons, ArduinoG27::SHIFTER_BLACK_BUTTON_DOWN)
		ANDPRINT(ShifterBlackButtons, ArduinoG27::SHIFTER_BLACK_BUTTON_LEFT)
		ANDPRINT(ShifterBlackButtons, ArduinoG27::SHIFTER_BLACK_BUTTON_RIGHT)
		OldShifterBlackButtons = ShifterBlackButtons;
	}

	uint8_t WheelShifters = G27.GetWheelShifters();
	static uint8_t OldWheelShifters;
	if(OldWheelShifters != WheelShifters) {
		IFPRINT(WheelShifters, ArduinoG27::WHEEL_SHIFTER_IDLE)
		ANDPRINT(WheelShifters, ArduinoG27::WHEEL_SHIFTER_LEFT)
		ANDPRINT(WheelShifters, ArduinoG27::WHEEL_SHIFTER_RIGHT)
		OldWheelShifters = WheelShifters;
	}

	uint8_t WheelButtons = G27.GetWheelButtons();
	static uint8_t OldWheelButtons;
	if(OldWheelButtons != WheelButtons) {
		IFPRINT(WheelButtons, ArduinoG27::WHEEL_BUTTON_IDLE)
		ANDPRINT(WheelButtons, ArduinoG27::WHEEL_BUTTON_LEFT_BOTTOM)
		ANDPRINT(WheelButtons, ArduinoG27::WHEEL_BUTTON_LEFT_MIDDLE)
		ANDPRINT(WheelButtons, ArduinoG27::WHEEL_BUTTON_LEFT_TOP)
		ANDPRINT(WheelButtons, ArduinoG27::WHEEL_BUTTON_RIGHT_BOTTOM)
		ANDPRINT(WheelButtons, ArduinoG27::WHEEL_BUTTON_RIGHT_MIDDLE)
		ANDPRINT(WheelButtons, ArduinoG27::WHEEL_BUTTON_RIGHT_TOP)
		OldWheelButtons = WheelButtons;
	}

	uint8_t ShifterRedButtons = G27.GetShifterRedButtons();
	static uint8_t OldShifterRedButtons;
	if(OldShifterRedButtons != ShifterRedButtons) {
		IFPRINT(ShifterRedButtons, ArduinoG27::SHIFTER_RED_BUTTON_IDLE)
		ANDPRINT(ShifterRedButtons, ArduinoG27::SHIFTER_RED_BUTTON_LEFT)
		ANDPRINT(ShifterRedButtons, ArduinoG27::SHIFTER_RED_BUTTON_MIDDLE_LEFT)
		ANDPRINT(ShifterRedButtons, ArduinoG27::SHIFTER_RED_BUTTON_MIDDLE_RIGHT)
		ANDPRINT(ShifterRedButtons, ArduinoG27::SHIFTER_RED_BUTTON_RIGHT)
		OldShifterRedButtons = ShifterRedButtons;
	}

	uint8_t ShifterGear = G27.GetShifterGear();
	static uint8_t OldShifterGear;
	if(OldShifterGear != ShifterGear) {
		IFPRINT(ShifterGear, ArduinoG27::SHIFTER_GEAR_IDLE)
		ANDPRINT(ShifterGear, ArduinoG27::SHIFTER_GEAR_1)
		ANDPRINT(ShifterGear, ArduinoG27::SHIFTER_GEAR_2)
		ANDPRINT(ShifterGear, ArduinoG27::SHIFTER_GEAR_3)
		ANDPRINT(ShifterGear, ArduinoG27::SHIFTER_GEAR_4)
		ANDPRINT(ShifterGear, ArduinoG27::SHIFTER_GEAR_5)
		ANDPRINT(ShifterGear, ArduinoG27::SHIFTER_GEAR_6)
		ANDPRINT(ShifterGear, ArduinoG27::SHIFTER_GEAR_REVERSE)
		OldShifterGear = ShifterGear;
	}
	
	static uint16_t OldWheel;
	NAMEPRINT(OldWheel, G27.GetWheel())
	static uint8_t OldThrottleRaw;
	NAMEPRINT(OldThrottleRaw, G27.GetThrottleRaw())
	static uint8_t OldBrakeRaw;
	NAMEPRINT(OldBrakeRaw, G27.GetBrakeRaw())
	static uint8_t OldClutchRaw;
	NAMEPRINT(OldClutchRaw, G27.GetClutchRaw())
	static uint8_t OldHorizontalShifter;
	//NAMEPRINT(OldHorizontalShifter, G27.GetHorizontalShifter()) // Very noisy
	static uint8_t OldVerticalShifter;
	//NAMEPRINT(OldVerticalShifter, G27.GetVerticalShifter()) // Very noisy too

	uint8_t VendorDefinedData = G27.GetVendorDefinedData();
	static uint8_t OldVendorDefinedData;
	if(OldVendorDefinedData != VendorDefinedData) {
		IFPRINT(VendorDefinedData, ArduinoG27::VENDOR_DEFINED_NONE)
		ANDPRINT(VendorDefinedData, ArduinoG27::VENDOR_DEFINED_1)
		ANDPRINT(VendorDefinedData, ArduinoG27::AC_POWER_ON)
		ANDPRINT(VendorDefinedData, ArduinoG27::VENDOR_DEFINED_3)
		ANDPRINT(VendorDefinedData, ArduinoG27::VENDOR_DEFINED_4)
		ANDPRINT(VendorDefinedData, ArduinoG27::VENDOR_DEFINED_5)
		ANDPRINT(VendorDefinedData, ArduinoG27::SHIFTER_GEAR_PRESSED)
		ANDPRINT(VendorDefinedData, ArduinoG27::VENDOR_DEFINED_7)
		OldVendorDefinedData = VendorDefinedData;
	}
	
	static int16_t OldHatSwitchDegrees;
	NAMEPRINT(OldHatSwitchDegrees, G27.GetHatSwitchDegrees())
	static int16_t OldWheelCentered;
	NAMEPRINT(OldWheelCentered, G27.GetWheelCentered())
	static bool OldUsingManualGearShifter;
	NAMEPRINT(OldUsingManualGearShifter, G27.UsingManualGearShifter())
	static uint8_t OldThrottle;
	NAMEPRINT(OldThrottle, G27.GetThrottle())
	static uint8_t OldBrake;
	NAMEPRINT(OldBrake, G27.GetBrake())
	static uint8_t OldClutch;
	NAMEPRINT(OldClutch, G27.GetClutch())
	static int8_t OldGearNumber;
	NAMEPRINT(OldGearNumber, G27.GetGearNumber())

}
