/*
 * Logitech G27 Library for Arduino
 * (c) 2018 Luca Anastasio
 * anastasio.lu@gmail.com
 * www.fablaquila.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef ARDUINOG27EVENTS_H_
#define ARDUINOG27EVENTS_H_

#include "ArduinoG27.h"



class ArduinoG27events : public ArduinoG27 {
public:

	ArduinoG27events(Stream* SerialPort) : ArduinoG27() { _Serial = SerialPort; }
	ArduinoG27events() : ArduinoG27() { _Serial = &Serial; }

private:

	Stream* _Serial;

#define ANDPRINT(a, b) if(a & b) _Serial->println(F(#b));
#define IFPRINT(a, b) if(a == b) _Serial->println(F(#b));
#define NAMEPRINT(a) _Serial->print(F(#a": ")); _Serial->println(a);

	void OnHatSwitchChange() {
		uint8_t HatSwitch = GetHatSwitch();
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_IDLE)
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_UP)
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_DOWN)
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_LEFT)
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_RIGHT)
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_UP_RIGHT)
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_DOWN_RIGHT)
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_UP_LEFT)
		IFPRINT(HatSwitch, ArduinoG27::HAT_SWITCH_DOWN_LEFT)
	}
	void OnShifterBlackButtonsChange() {
		uint8_t ShifterBlackButtons = GetShifterBlackButtons();
		IFPRINT(ShifterBlackButtons, ArduinoG27::SHIFTER_BLACK_BUTTON_IDLE)
		ANDPRINT(ShifterBlackButtons, ArduinoG27::SHIFTER_BLACK_BUTTON_UP)
		ANDPRINT(ShifterBlackButtons, ArduinoG27::SHIFTER_BLACK_BUTTON_DOWN)
		ANDPRINT(ShifterBlackButtons, ArduinoG27::SHIFTER_BLACK_BUTTON_LEFT)
		ANDPRINT(ShifterBlackButtons, ArduinoG27::SHIFTER_BLACK_BUTTON_RIGHT)
	}
	void OnShifterRedButtonsChange() {
		uint8_t ShifterRedButtons = GetShifterRedButtons();
		IFPRINT(ShifterRedButtons, ArduinoG27::SHIFTER_RED_BUTTON_IDLE)
		ANDPRINT(ShifterRedButtons, ArduinoG27::SHIFTER_RED_BUTTON_LEFT)
		ANDPRINT(ShifterRedButtons, ArduinoG27::SHIFTER_RED_BUTTON_MIDDLE_LEFT)
		ANDPRINT(ShifterRedButtons, ArduinoG27::SHIFTER_RED_BUTTON_MIDDLE_RIGHT)
		ANDPRINT(ShifterRedButtons, ArduinoG27::SHIFTER_RED_BUTTON_RIGHT)
	}
	void OnWheelShiftersChange() {
		uint8_t WheelShifters = GetWheelShifters();
		IFPRINT(WheelShifters, ArduinoG27::WHEEL_SHIFTER_IDLE)
		ANDPRINT(WheelShifters, ArduinoG27::WHEEL_SHIFTER_LEFT)
		ANDPRINT(WheelShifters, ArduinoG27::WHEEL_SHIFTER_RIGHT)
	}
	void OnWheelButtonsChange() {
		uint8_t WheelButtons = GetWheelButtons();
		IFPRINT(WheelButtons, ArduinoG27::WHEEL_BUTTON_IDLE)
		ANDPRINT(WheelButtons, ArduinoG27::WHEEL_BUTTON_LEFT_BOTTOM)
		ANDPRINT(WheelButtons, ArduinoG27::WHEEL_BUTTON_LEFT_MIDDLE)
		ANDPRINT(WheelButtons, ArduinoG27::WHEEL_BUTTON_LEFT_TOP)
		ANDPRINT(WheelButtons, ArduinoG27::WHEEL_BUTTON_RIGHT_BOTTOM)
		ANDPRINT(WheelButtons, ArduinoG27::WHEEL_BUTTON_RIGHT_MIDDLE)
		ANDPRINT(WheelButtons, ArduinoG27::WHEEL_BUTTON_RIGHT_TOP)
	}
	void OnWheelChange() {
		NAMEPRINT(GetWheel())
		NAMEPRINT(GetWheelCentered())
	}
	void OnShifterGearChange() {
		uint8_t ShifterGear = GetShifterGear();
		IFPRINT(ShifterGear, ArduinoG27::SHIFTER_GEAR_IDLE)
		ANDPRINT(ShifterGear, ArduinoG27::SHIFTER_GEAR_1)
		ANDPRINT(ShifterGear, ArduinoG27::SHIFTER_GEAR_2)
		ANDPRINT(ShifterGear, ArduinoG27::SHIFTER_GEAR_3)
		ANDPRINT(ShifterGear, ArduinoG27::SHIFTER_GEAR_4)
		ANDPRINT(ShifterGear, ArduinoG27::SHIFTER_GEAR_5)
		ANDPRINT(ShifterGear, ArduinoG27::SHIFTER_GEAR_6)
		ANDPRINT(ShifterGear, ArduinoG27::SHIFTER_GEAR_REVERSE)
	}
	void OnGearNumberChange() {
		NAMEPRINT(GetGearNumber())
	}
	void OnThrottleChange() {
		NAMEPRINT(GetThrottleRaw())
		NAMEPRINT(GetThrottle())
	}
	void OnBrakeChange() {
		NAMEPRINT(GetBrakeRaw())
		NAMEPRINT(GetBrake())
	}
	void OnClutchChange() {
		NAMEPRINT(GetClutchRaw())
		NAMEPRINT(GetClutch())
	}
	void OnRawShifterChange() {
		//NAMEPRINT(GetHorizontalShifter())
		//NAMEPRINT(GetVerticalShifter())
	}
	void OnVendorDefinedDataChange() {
		uint8_t VendorDefinedData = GetVendorDefinedData();
		IFPRINT(VendorDefinedData, ArduinoG27::VENDOR_DEFINED_NONE)
		ANDPRINT(VendorDefinedData, ArduinoG27::VENDOR_DEFINED_1)
		ANDPRINT(VendorDefinedData, ArduinoG27::AC_POWER_ON)
		ANDPRINT(VendorDefinedData, ArduinoG27::VENDOR_DEFINED_3)
		ANDPRINT(VendorDefinedData, ArduinoG27::VENDOR_DEFINED_4)
		ANDPRINT(VendorDefinedData, ArduinoG27::VENDOR_DEFINED_5)
		ANDPRINT(VendorDefinedData, ArduinoG27::SHIFTER_GEAR_PRESSED)
		ANDPRINT(VendorDefinedData, ArduinoG27::VENDOR_DEFINED_7)
	}

};

#endif /* ARDUINOG27EVENTS_H_ */
