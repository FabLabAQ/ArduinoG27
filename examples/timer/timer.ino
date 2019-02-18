/*
 * Timer for the race track
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

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int triggerPort = 9;
const int echoPort = 10;
long t0, t, duty, distance;
int m, s, d;

void setup() {
  lcd.begin(16, 2);
  pinMode(triggerPort, OUTPUT);
  pinMode(echoPort, INPUT);
}

void loop() {
  lcd.setCursor(0, 0);
  t = millis() - t0;
  printAll();
  measure();
  if (distance < 15)
  {
    t = millis() - t0;
    lcd.clear();
    lcd.setCursor(0, 1);
    printAll();
    while (distance < 15 ) {
      measure();
      delay(500);
    }
    delay(10);
    t0 = millis();
  }
}

void measure() {
  digitalWrite( triggerPort, LOW );
  digitalWrite( triggerPort, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( triggerPort, LOW );
  duty = pulseIn( echoPort, HIGH );
  distance = 0.034 * duty / 2;
}

void printAll() {
  m = t / 60000;
  s = (t - m * 60000) / 1000;
  d = t%100;
  if (s < 10 && d < 10) {
    lcd.print("0"); lcd.print(m); lcd.print(":"); lcd.print("0"); lcd.print(s); lcd.print(":"); lcd.print("0"); lcd.print(d);
  }
  else {
    if (s < 10) {
      lcd.print("0"); lcd.print(m); lcd.print(":"); lcd.print("0"); lcd.print(s); lcd.print(":"); lcd.print(d);
    }
    else {
      if (d < 10) {
        lcd.print("0"); lcd.print(m); lcd.print(":"); lcd.print(s); lcd.print(":");  lcd.print("0"); lcd.print(d);
      }
      else {
        lcd.print("0"); lcd.print(m); lcd.print(":"); lcd.print(s); lcd.print(":"); lcd.print(d);
      }
    }
  }
}
