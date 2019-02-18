/*
 * Serial receiver to be used on an RC car in conjunction with the sender example
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

#include <Servo.h>

Servo steeringServo;
Servo motorESC;

#define SERVO_PIN 9
#define ESC_PIN 10
#define TIMEOUT 20
#define MIN_THROTTLE 4
#define THROTTLE_MAX 16
#define MIN_BRAKE -4
#define BRAKE_OFFSET -20
#define THROTTLE_OFFSET 70
#define ESC_IDLE_US 1500
#define SERVO_IDLE_US 1350
#define PACKET_BEGIN 0x5
#define PACKET_END 0xA


typedef struct {
  uint8_t begin : 4;
  uint8_t reverse : 1;
  int16_t throttle : 9;
  int16_t steering : 14;
  uint8_t end : 4;
} packet_t;

void setup() {
	Serial.begin(9600);
	steeringServo.attach(SERVO_PIN);
	steeringServo.writeMicroseconds(SERVO_IDLE_US);
	motorESC.attach(ESC_PIN);
	motorESC.writeMicroseconds(ESC_IDLE_US);
}

uint32_t lastMillis;
int16_t previousThrottle1 = 0;
int16_t previousThrottle2 = 0;

void loop() {
	if (millis() > lastMillis + TIMEOUT) {
		motorESC.writeMicroseconds(ESC_IDLE_US);
	}
	if (Serial.available() == sizeof(packet_t)) {
		packet_t packet;
		Serial.readBytes((char*)&packet, sizeof(packet_t));
		if (packet.begin == PACKET_BEGIN && packet.end == PACKET_END) {
			lastMillis = millis();
			int16_t steering_us = SERVO_IDLE_US + (packet.steering/16);
			steeringServo.writeMicroseconds(steering_us);
			int16_t throttle_us;
			
			if(packet.throttle > MIN_THROTTLE) {
				throttle_us = ESC_IDLE_US + (packet.throttle / 4) + THROTTLE_OFFSET;
				if (throttle_us > THROTTLE_MAX) throttle_us = ESC_IDLE_US + THROTTLE_MAX + THROTTLE_OFFSET;
			}
			else if(packet.throttle < MIN_BRAKE) {
				throttle_us = ESC_IDLE_US + (packet.throttle / 2) + BRAKE_OFFSET;
			}
			else throttle_us = ESC_IDLE_US;

			previousThrottle2 = previousThrottle1;
			previousThrottle1 = packet.throttle;
			motorESC.writeMicroseconds(throttle_us);
		}
		else while(Serial.available() > 0) Serial.read();
	}
}
