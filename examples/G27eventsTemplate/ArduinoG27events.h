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

//------------------------------- Template file to implement event functions -------------------------------

class ArduinoG27events : public ArduinoG27 {
public:

	ArduinoG27events() {}

private:

	void OnHatSwitchChange() {}
	void OnShifterBlackButtonsChange() {}
	void OnShifterRedButtonsChange() {}
	void OnWheelShiftersChange() {}
	void OnWheelButtonsChange() {}
	void OnWheelChange() {}
	void OnShifterGearChange() {}
	void OnGearNumberChange() {}
	void OnThrottleChange() {}
	void OnBrakeChange() {}
	void OnClutchChange() {}
	void OnRawShifterChange() {}
	void OnVendorDefinedDataChange() {}

};

#endif /* ARDUINOG27EVENTS_H_ */
