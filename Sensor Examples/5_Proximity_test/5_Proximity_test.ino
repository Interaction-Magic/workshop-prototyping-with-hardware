/*
 * ©️2026 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

 // Include this for Serial to work. You do NOT need to install any libraries for this
#include <Adafruit_TinyUSB.h>

// Install the library "Adafruit APDS9960"
#include <Adafruit_APDS9960.h>

Adafruit_APDS9960 apds9960;
uint8_t proximity;

// Trigger and reset thresholds
const float threshold_trigger = 30;
const float threshold_reset = 5;

// Flag to keep track of whether we have triggered
bool has_triggered = false;

void setup(void) {
	Serial.begin(9600);

	// Initialise the proximity sensor
	apds9960.begin();
	apds9960.enableProximity(true);
}

void loop(void) {
	proximity = apds9960.readProximity();

	Serial.print("Proximity: ");
	Serial.println(proximity);

	// Trigger if proximity is above threshold
	if(!has_triggered && (proximity >= threshold_trigger)){
		Serial.println("Triggered!");
		has_triggered = true;
	}

	// Reset when proximity goes below threshold
	if(has_triggered && (proximity <= threshold_reset)){
		Serial.println("Reset!");
		has_triggered = false;
	}	

	delay(100);
}