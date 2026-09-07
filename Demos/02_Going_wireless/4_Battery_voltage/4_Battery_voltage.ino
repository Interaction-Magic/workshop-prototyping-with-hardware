/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// For Serial
#include <Adafruit_TinyUSB.h> 

// Create variable for battery pin
const int battery_pin = A6;

void setup() {
	Serial.begin(9600);
}

void loop() {

	// Read in battery level
	float battery_voltage = analogRead(battery_pin);

	// Scale to correct voltage based on Feather Sense's voltage divider
	battery_voltage = (battery_voltage*7.2)/1024;

	Serial.print(battery_voltage);
	Serial.println("V");

	delay(200);
}
