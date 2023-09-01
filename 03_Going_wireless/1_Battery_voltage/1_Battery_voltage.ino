/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// For Serial
#include <Adafruit_TinyUSB.h> 

// Create variables for pins
const int battery_pin = A6;

void setup() {
	Serial.begin(9600);
}

void loop() {

	float battery_voltage = analogRead(battery_pin);
	battery_voltage = (battery_voltage*7.2)/1024;

	Serial.print(battery_voltage);
	Serial.println("V");

	delay(200);
}
