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

#ifndef ARDUINOG27_H_
#define ARDUINOG27_H_

#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include <SPI.h>

class ArduinoG27: public HIDReportParser {
private:
	USB _Usb;
	HIDUniversal _Hid;

	typedef struct {
		uint8_t HatSwitchData : 4;
		uint8_t ShifterBlackButtonsData : 4;
		uint8_t WheelShiftersData : 2;
		uint8_t WheelButtonsTopData : 2;
		uint8_t ShifterRedButtonsData : 4;
		uint8_t ShifterGearData : 6;
		uint8_t WheelButtonsBottomData : 4;
		uint16_t WheelData : 14;
		uint8_t ThrottleData : 8;
		uint8_t BrakeData : 8;
		uint8_t ClutchData : 8;
		uint8_t HorizontalShifterData : 8;
		uint8_t VerticalShifterData : 8;
		uint8_t ReverseGearData : 1;
		uint8_t VendorDefinedData : 7;
	} G27_raw_data_t;

	typedef struct {
		uint8_t HatSwitchData = 0;
		uint8_t ShifterBlackButtonsData = 0;
		uint8_t WheelShiftersData = 0;
		uint8_t WheelButtonsData = 0;
		uint8_t ShifterRedButtonsData = 0;
		uint8_t ShifterGearData = 0;
		uint16_t WheelData = 0;
		uint8_t ThrottleData = 0;
		uint8_t BrakeData = 0;
		uint8_t ClutchData = 0;
		uint8_t HorizontalShifterData = 0;
		uint8_t VerticalShifterData = 0;
		uint8_t VendorDefinedData = 0;
	} G27_data_t;

	G27_data_t _G27_data;

	int8_t _GearNumber = 0;
	uint16_t _WheelChangeThreshold = 0xFFFF;
	uint8_t _ThrottleChangeThreshold = 0xFF;
	uint8_t _BrakeChangeThreshold = 0xFF;
	uint8_t _ClutchChangeThreshold = 0xFF;
	uint8_t _HorizontalShifterChangeThreshold = 0xFF;
	uint8_t _VerticalShifterChangeThreshold = 0xFF;
	bool _UsingManualGearShifter = false;
	uint8_t _LEDs = 0;
	uint16_t _WheelRange = 270;
	uint8_t _AutoCenterStrength = 0x07;
	uint8_t _StrengthRisingRate = 0xFF;
	uint8_t _WheelForce = 0;
	uint8_t _LeftFriction = 0;
	uint8_t _RightFriction = 0;

protected:

	virtual void OnHatSwitchChange() {}
	virtual void OnShifterBlackButtonsChange() {}
	virtual void OnShifterRedButtonsChange() {}
	virtual void OnWheelShiftersChange() {}
	virtual void OnWheelButtonsChange() {}
	virtual void OnWheelChange() {}
	virtual void OnShifterGearChange() {}
	virtual void OnGearNumberChange() {}
	virtual void OnThrottleChange() {}
	virtual void OnBrakeChange() {}
	virtual void OnClutchChange() {}
	virtual void OnRawShifterChange() {}
	virtual void OnVendorDefinedDataChange() {}

public:

	enum hat_switch_t : uint8_t {
		HAT_SWITCH_UP,
		HAT_SWITCH_UP_RIGHT,
		HAT_SWITCH_RIGHT ,
		HAT_SWITCH_DOWN_RIGHT,
		HAT_SWITCH_DOWN ,
		HAT_SWITCH_DOWN_LEFT,
		HAT_SWITCH_LEFT ,
		HAT_SWITCH_UP_LEFT,
		HAT_SWITCH_IDLE
	};

	enum shifter_black_button_t : uint8_t {
		SHIFTER_BLACK_BUTTON_IDLE,
		SHIFTER_BLACK_BUTTON_DOWN,
		SHIFTER_BLACK_BUTTON_LEFT,
		SHIFTER_BLACK_BUTTON_RIGHT = 4,
		SHIFTER_BLACK_BUTTON_UP = 8
	};

	enum wheel_shifter_t : uint8_t {
		WHEEL_SHIFTER_IDLE,
		WHEEL_SHIFTER_RIGHT,
		WHEEL_SHIFTER_LEFT
	};

	enum wheel_button_t : uint8_t {
		WHEEL_BUTTON_IDLE,
		WHEEL_BUTTON_RIGHT_TOP,
		WHEEL_BUTTON_LEFT_TOP,
		WHEEL_BUTTON_RIGHT_MIDDLE = 4,
		WHEEL_BUTTON_RIGHT_BOTTOM = 8,
		WHEEL_BUTTON_LEFT_MIDDLE = 16,
		WHEEL_BUTTON_LEFT_BOTTOM = 32,

	};

	enum shifter_red_button_t : uint8_t {
		SHIFTER_RED_BUTTON_IDLE,
		SHIFTER_RED_BUTTON_MIDDLE_LEFT,
		SHIFTER_RED_BUTTON_MIDDLE_RIGHT,
		SHIFTER_RED_BUTTON_RIGHT = 4,
		SHIFTER_RED_BUTTON_LEFT = 8
	};

	enum shifter_gear_t : uint8_t {
		SHIFTER_GEAR_IDLE,
		SHIFTER_GEAR_REVERSE,
		SHIFTER_GEAR_1,
		SHIFTER_GEAR_2 = 4,
		SHIFTER_GEAR_3 = 8,
		SHIFTER_GEAR_4 = 16,
		SHIFTER_GEAR_5 = 32,
		SHIFTER_GEAR_6 = 64
	};

	enum vendor_defined_t : uint8_t {
		VENDOR_DEFINED_NONE,
		VENDOR_DEFINED_1,
		AC_POWER_ON,
		VENDOR_DEFINED_3 = 4,
		VENDOR_DEFINED_4 = 8,
		VENDOR_DEFINED_5 = 16,
		SHIFTER_GEAR_PRESSED = 32,
		VENDOR_DEFINED_7 = 64
	};

	enum set_leds_t : uint8_t {
		SET_LEDS_NONE,
		SET_LEDS_GREEN_1,
		SET_LEDS_GREEN_2,
		SET_LEDS_YELLOW_1 = 4,
		SET_LEDS_YELLOW_2 = 8,
		SET_LEDS_RED = 16,
		SET_LEDS_ALL = 31
	};


	ArduinoG27(): _Hid(&_Usb) {}

	void Init() {
		_Usb.Init();
		_Hid.SetReportParser(0, this);

		while (!_Hid.isReady()) _Usb.Task();

		uint8_t initCmd1[] = {0xf8, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00};
		_Hid.SndRpt(7, initCmd1);
		_Usb.Task();

		uint8_t initCmd2[] = {0xf8, 0x09, 0x04, 0x01, 0x00, 0x00, 0x00};
		_Hid.SndRpt(7, initCmd2);
		_Usb.Task();

		// TODO: find a "cleaner" way to re-enumerate after enabling native mode
		_Usb.Init();

	}
	
	bool Ready() { _Usb.Task(); return (_G27_data.VendorDefinedData & AC_POWER_ON); }

	void Task() { _Usb.Task(); }

	void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
		G27_raw_data_t* RawData = (G27_raw_data_t*)buf;

		if(RawData->HatSwitchData != _G27_data.HatSwitchData) {
			_G27_data.HatSwitchData = RawData->HatSwitchData;
			OnHatSwitchChange();
		}
		if(RawData->ShifterBlackButtonsData != _G27_data.ShifterBlackButtonsData) {
			_G27_data.ShifterBlackButtonsData = RawData->ShifterBlackButtonsData;
			OnShifterBlackButtonsChange();
		}
		if(RawData->WheelShiftersData != _G27_data.WheelShiftersData) {
			_G27_data.WheelShiftersData = RawData->WheelShiftersData;
			_UsingManualGearShifter = false;
			if(_G27_data.WheelShiftersData == WHEEL_SHIFTER_LEFT) {
				if(_GearNumber > -1) _GearNumber--;
				OnGearNumberChange();
			}
			else if(_G27_data.WheelShiftersData == WHEEL_SHIFTER_RIGHT) {
				if(_GearNumber < 6) _GearNumber++;
				OnGearNumberChange();
			}
			OnWheelShiftersChange();
		}
		uint8_t WheelButtonsData = (RawData->WheelButtonsBottomData<<2) | RawData->WheelButtonsTopData;
		if(WheelButtonsData != _G27_data.WheelButtonsData) {
			_G27_data.WheelButtonsData = WheelButtonsData;
			OnWheelButtonsChange();
		}
		if(RawData->ShifterRedButtonsData != _G27_data.ShifterRedButtonsData) {
			_G27_data.ShifterRedButtonsData = RawData->ShifterRedButtonsData;
			OnShifterRedButtonsChange();
		}
		uint8_t ShifterGearData = (RawData->ShifterGearData<<1) | RawData->ReverseGearData;
		if(ShifterGearData != _G27_data.ShifterGearData) {
			_G27_data.ShifterGearData = ShifterGearData;
			switch (ShifterGearData) {
			case SHIFTER_GEAR_IDLE: _GearNumber = 0; break;
			case SHIFTER_GEAR_REVERSE: _GearNumber = -1; break;
			case SHIFTER_GEAR_6: _GearNumber = 6; break;
			case SHIFTER_GEAR_5: _GearNumber = 5; break;
			case SHIFTER_GEAR_4: _GearNumber = 4; break;
			case SHIFTER_GEAR_3: _GearNumber = 3; break;
			case SHIFTER_GEAR_2: _GearNumber = 2; break;
			case SHIFTER_GEAR_1: _GearNumber = 1; break;
			default: break;
			}
			_UsingManualGearShifter = true;
			OnGearNumberChange();
			OnShifterGearChange();
		}
		if((RawData->WheelData ^ _G27_data.WheelData) & _WheelChangeThreshold) {
			_G27_data.WheelData = RawData->WheelData;
			OnWheelChange();
		}
		if((RawData->ThrottleData ^ _G27_data.ThrottleData) & _ThrottleChangeThreshold) {
			_G27_data.ThrottleData = RawData->ThrottleData;
			OnThrottleChange();
		}
		if((RawData->BrakeData ^ _G27_data.BrakeData) & _BrakeChangeThreshold) {
			_G27_data.BrakeData = RawData->BrakeData;
			OnBrakeChange();
		}
		if((RawData->ClutchData ^ _G27_data.ClutchData) & _ClutchChangeThreshold) {
			_G27_data.ClutchData = RawData->ClutchData;
			OnClutchChange();
		}
		if((RawData->HorizontalShifterData ^ _G27_data.HorizontalShifterData) & _HorizontalShifterChangeThreshold) {
			_G27_data.HorizontalShifterData = RawData->HorizontalShifterData;
			OnRawShifterChange();
		}
		if((RawData->VerticalShifterData ^ _G27_data.VerticalShifterData) & _VerticalShifterChangeThreshold) {
			_G27_data.VerticalShifterData = RawData->VerticalShifterData;
			OnRawShifterChange();
		}
		if(RawData->VendorDefinedData != _G27_data.VendorDefinedData) {
			_G27_data.VendorDefinedData = RawData->VendorDefinedData;
			OnVendorDefinedDataChange();
		}
	}

	// Untouched data return
	
	uint8_t GetHatSwitch() { return _G27_data.HatSwitchData; }
	
	uint8_t GetShifterBlackButtons() { return _G27_data.ShifterBlackButtonsData; }
	
	uint8_t GetWheelShifters() { return _G27_data.WheelShiftersData; }
	
	uint8_t GetWheelButtons() { return _G27_data.WheelButtonsData; }
	
	uint8_t GetShifterRedButtons() { return _G27_data.ShifterRedButtonsData; }
	
	uint8_t GetShifterGear() { return _G27_data.ShifterGearData; }
	
	uint16_t GetWheel() { return _G27_data.WheelData; }
	
	uint8_t GetThrottleRaw() { return _G27_data.ThrottleData; }
	
	uint8_t GetBrakeRaw() { return _G27_data.BrakeData; }
	
	uint8_t GetClutchRaw() { return _G27_data.ClutchData; }
	
	uint8_t GetHorizontalShifter() { return _G27_data.HorizontalShifterData; }
	
	uint8_t GetVerticalShifter() { return _G27_data.VerticalShifterData; }
	
	uint8_t GetVendorDefinedData() { return _G27_data.VendorDefinedData; }
	
	// Elaborated data return
	
	int16_t GetHatSwitchDegrees() { return _G27_data.HatSwitchData == 8 ? -1 : _G27_data.HatSwitchData*45; }
	
	int16_t GetWheelCentered() { return _G27_data.WheelData - 8192; }
	
	// GetWheelDegrees?
	
	bool UsingManualGearShifter() { return _UsingManualGearShifter; }
	
	uint8_t GetThrottle() { return 255 - _G27_data.ThrottleData; }
	
	uint8_t GetBrake() { return 255 - _G27_data.BrakeData; }
	
	uint8_t GetClutch() { return 255 - _G27_data.ClutchData; }
	
	int8_t GetGearNumber() { return _GearNumber; }
	
	uint8_t GetLEDs() { return _LEDs; }
	
	uint16_t GetWheelRange() { return _WheelRange; }
	
	uint8_t GetAutoCenterStrength() { return _AutoCenterStrength; }
	
	uint8_t GetStrengthRisingRate() { return _StrengthRisingRate; }
	
	uint8_t GetWheelForce() { return _WheelForce; }
	
	uint8_t GetWheelLeftFriction() { return _LeftFriction; }
	
	uint8_t GetWheelRightFriction() { return _RightFriction; }
	
	

	void SetWheelChangeThreshold(uint8_t LSBs) { if(LSBs <14) _WheelChangeThreshold = 0xFFFF << LSBs; }
	
	void SetThrottleChangeThreshold(uint8_t LSBs) { if(LSBs <8) _ThrottleChangeThreshold = 0xFF << LSBs; }
	
	void SetBrakeChangeThreshold(uint8_t LSBs) { if(LSBs <8) _BrakeChangeThreshold = 0xFF << LSBs; }
	
	void SetClutchChangeThreshold(uint8_t LSBs) { if(LSBs <8) _ClutchChangeThreshold = 0xFF << LSBs; }
	
	void SetHorizontalShifterChangeThreshold(uint8_t LSBs) { if(LSBs <8) _HorizontalShifterChangeThreshold = 0xFF << LSBs; }
	
	void SetVerticalShifterChangeThreshold(uint8_t LSBs) { if(LSBs <8) _VerticalShifterChangeThreshold = 0xFF << LSBs; }
	

	void SetLEDs(uint8_t LEDs) {
		_LEDs = LEDs;
		uint8_t LEDs_cmd[] = {0xf8, 0x12, LEDs, 0x00, 0x00, 0x00, 0x01};
		_Hid.SndRpt(7, LEDs_cmd);
		_Usb.Task();
	}
	
	void SetWheelRange(uint16_t Range) {
		if(Range <= 900 && Range >= 270) {
			_WheelRange = Range;
			uint8_t RangeLSB = Range & 0x00FF;
			uint8_t RangeMSB = (Range & 0xFF00) >> 8;
			uint8_t SetRangeCmd[] = {0xf8, 0x81, RangeLSB, RangeMSB, 0x00, 0x00, 0x00};
			_Hid.SndRpt(7, SetRangeCmd);
			_Usb.Task();
		}
	}
	
	void SetWheelAutoCenter(int8_t Strength = 0x07, uint8_t StrengthRisingRate = 0xFF) {
		_StrengthRisingRate = StrengthRisingRate;
		if(Strength == -1) {
			_AutoCenterStrength = -1;
			uint8_t AutoCenterOffCmd[] = {0xf5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
			_Hid.SndRpt(7, AutoCenterOffCmd);
			_Usb.Task();
		}
		else if(Strength <= 15) {
			if(_AutoCenterStrength == -1) {
				uint8_t AutoCenterOnCmd[] = {0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
				_Hid.SndRpt(7, AutoCenterOnCmd);
				_Usb.Task();
			}
			_AutoCenterStrength = Strength;
			uint8_t AutoCenterStrengthCmd[] = {0xFE, 0x0D, Strength, Strength, StrengthRisingRate, 0x00, 0x00};
			_Hid.SndRpt(7, AutoCenterStrengthCmd);
			_Usb.Task();
		}
	}
	
	void SetWheelConstantForce(int8_t Force) {
		_WheelForce = Force;
		if(Force == -128 || Force == 0) DisableWheelEffects(1);
		else {
			uint8_t ConstantForceCmd[] = {0x11, 0x00, 127-Force, 0x00, 0x00, 0x00, 0x00};
			_Hid.SndRpt(7, ConstantForceCmd);
			_Usb.Task();
		}
	}
	
	void SetWheelFriction(uint8_t Friction) {
		SetWheelFriction(Friction, Friction);
	}
	
	void SetWheelFriction(uint8_t LeftFriction, uint8_t RightFriction) {
		if(LeftFriction == 0 && RightFriction == 0) {
			_LeftFriction = 0;
			_RightFriction = 0;
			DisableWheelEffects(2);
		}
		else if(LeftFriction <= 15 && RightFriction <= 15) {
			_LeftFriction = LeftFriction;
			_RightFriction = RightFriction;
			uint8_t FrictionCmd[] = {0x21, 0x02, LeftFriction, 0x00, RightFriction, 0x00, 0x00};
			_Hid.SndRpt(7, FrictionCmd);
			_Usb.Task();
		}
	}
	
	void DisableWheelEffects(uint8_t Slot = 0) {
		if(Slot == 0) Slot = 0xF3;
		else Slot <<= 4;
		uint8_t EffectsDisableCmd[] = {Slot, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		_Hid.SndRpt(7, EffectsDisableCmd);
		_Usb.Task();
	}

};

#endif /* ARDUINOG27_H_ */