/*
 * Logitech G27 serial sender example with lock pin
 * (c) 2018 FabLabAQ
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

#include "ArduinoG27.h"

ArduinoG27 G27;

#define REFRESH_MS 10
#define BAUDRATE 9600
#define PACKET_BEGIN 0x5
#define PACKET_END 0xA

const char unlockCode[] = {
  ArduinoG27::SHIFTER_BLACK_BUTTON_DOWN,
  ArduinoG27::SHIFTER_BLACK_BUTTON_UP,
  ArduinoG27::SHIFTER_BLACK_BUTTON_LEFT,
  ArduinoG27::SHIFTER_BLACK_BUTTON_RIGHT
};

uint32_t startMillis = 0;

const uint8_t LEDs[] = {
  ArduinoG27::SET_LEDS_NONE,
  ArduinoG27::SET_LEDS_RED,
  ArduinoG27::SET_LEDS_GREEN_1,
  ArduinoG27::SET_LEDS_GREEN_1 | ArduinoG27::SET_LEDS_GREEN_2,
  ArduinoG27::SET_LEDS_GREEN_1 | ArduinoG27::SET_LEDS_GREEN_2 | ArduinoG27::SET_LEDS_YELLOW_1,
  ArduinoG27::SET_LEDS_GREEN_1 | ArduinoG27::SET_LEDS_GREEN_2 | ArduinoG27::SET_LEDS_YELLOW_1 | ArduinoG27::SET_LEDS_YELLOW_2,
  ArduinoG27::SET_LEDS_GREEN_1 | ArduinoG27::SET_LEDS_GREEN_2 | ArduinoG27::SET_LEDS_YELLOW_1 | ArduinoG27::SET_LEDS_YELLOW_2 | ArduinoG27::SET_LEDS_RED
};

#define MAX_TIME 60000*5.0

const uint32_t times[] = {
  MAX_TIME * 0.25,
  MAX_TIME * 0.5,
  MAX_TIME * 0.75,
  MAX_TIME,
};

//typedef struct {
//  uint8_t begin : 4;
//  uint8_t reverse : 1;
//  int16_t throttle : 9;
//  int16_t steering : 14;
//  uint8_t end : 4;
//} packet_t;

typedef struct {
  int16_t throttle : 4;
  int16_t steering : 4;
} packet_t;

#define STATE_IDLE false
#define STATE_RUN true

PacketSerial packetSerial;

void setup()
{
  packetSerial.begin(9600);
  G27.Init();
  while(!G27.Ready());
  G27.SetWheelAutoCenter(0);
  G27.SetWheelFriction(0);
  G27.SetWheelRange(270);
}

void fsm1_idle() {
  uint8_t button = G27.GetShifterBlackButtons();
  static uint8_t prevButton = ArduinoG27::SHIFTER_BLACK_BUTTON_IDLE;
  if (button != ArduinoG27::SHIFTER_BLACK_BUTTON_IDLE && button != prevButton) {
  	G27.SetLEDs(LEDs[0]);
  	static char insertedCode[sizeof(unlockCode)];
	static uint8_t codeIndex = 0;
    insertedCode[codeIndex++] = button;
    if (codeIndex == sizeof(unlockCode)) {
      if (strncmp(unlockCode, insertedCode, sizeof(unlockCode)) == 0) {
        fsm1_state = FSM1_STATE_RUN;
        startMillis = millis();
        G27.SetLEDs(LEDs[2]);
      }
      else G27.SetLEDs(LEDs[1]);
      codeIndex = 0;
    }
  }
  prevButton = button;
}

void fsm1_run() {
  static uint32_t lastMillis;
  if (millis() > lastMillis + REFRESH) {
    packet_t packet;
    packet.reverse = G27.GetShifterRedButtons() & ArduinoG27::SHIFTER_RED_BUTTON_RIGHT;
    packet.steering = G27.GetWheelCentered();
    uint8_t brake = G27.GetBrake();
    if(brake > 0) {
    	packet.throttle = - (brake>>5);
    }
    else packet.throttle = G27.GetThrottle()>>5;
	packet.begin = PACKET_BEGIN;
	packet.end = PACKET_END;
    Serial.write((char)packet);
    lastMillis = millis();
  }

	uint32_t elapsedTime = millis() - startMillis;
  if (elapsedTime > times[3]) {
    G27.SetLEDs(LEDs[6]);
    fsm1_state = FSM1_STATE_IDLE;
  }
  else if (elapsedTime > times[2]) G27.SetLEDs(LEDs[5]);
  else if (elapsedTime > times[1]) G27.SetLEDs(LEDs[4]);
  else if (elapsedTime > times[0]) G27.SetLEDs(LEDs[3]);
}

void loop()
{
  static bool state = STATE_IDLE;
  if (state == STATE_RUN) {
  	static uint32_t lastMillis;
  if (millis() > lastMillis + REFRESH) {
    packet_t packet;
    packet.reverse = G27.GetShifterRedButtons() & ArduinoG27::SHIFTER_RED_BUTTON_RIGHT;
    packet.steering = G27.GetWheelCentered();
    uint8_t brake = G27.GetBrake();
    if(brake > 0) {
    	packet.throttle = - (brake>>5);
    }
    else packet.throttle = G27.GetThrottle()>>5;
	packet.begin = PACKET_BEGIN;
	packet.end = PACKET_END;
    Serial.write((char)packet);
    lastMillis = millis();
  }

	uint32_t elapsedTime = millis() - startMillis;
  if (elapsedTime > times[3]) {
    G27.SetLEDs(LEDs[6]);
    state = STATE_IDLE;
  }
  else if (elapsedTime > times[2]) G27.SetLEDs(LEDs[5]);
  else if (elapsedTime > times[1]) G27.SetLEDs(LEDs[4]);
  else if (elapsedTime > times[0]) G27.SetLEDs(LEDs[3]);
  }
  else {
  	uint8_t button = G27.GetShifterBlackButtons();
  static uint8_t prevButton = ArduinoG27::SHIFTER_BLACK_BUTTON_IDLE;
  if (button != ArduinoG27::SHIFTER_BLACK_BUTTON_IDLE && button != prevButton) {
  	G27.SetLEDs(LEDs[0]);
  	static char insertedCode[sizeof(unlockCode)];
	static uint8_t codeIndex = 0;
    insertedCode[codeIndex++] = button;
    if (codeIndex == sizeof(unlockCode)) {
      if (strncmp(unlockCode, insertedCode, sizeof(unlockCode)) == 0) {
        state = STATE_RUN;
        startMillis = millis();
        G27.SetLEDs(LEDs[2]);
      }
      else G27.SetLEDs(LEDs[1]);
      codeIndex = 0;
    }
  }
  prevButton = button;
  }
  G27.Task();
}
