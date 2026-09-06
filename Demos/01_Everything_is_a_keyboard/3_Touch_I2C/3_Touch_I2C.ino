/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// Include this for Serial to work. You do NOT need to install any libraries for this
#include <Adafruit_TinyUSB.h>

#include <Adafruit_CAP1188.h>

// Create reference to touch board
Adafruit_CAP1188 cap = Adafruit_CAP1188();

void setup() {
	Serial.begin(9600);

	if(!cap.begin()){
		// If we can't begin the sensor, print debug message
		while(true){
			Serial.println("CAP1188 not found");
			delay(500);
		}
	}
}

void loop() {
	uint8_t touched = cap.touched();

	if (touched > 0) {
		// We detected a touch!

		for (uint8_t i=0; i<8; i++) {
			if (touched & (1 << i)) {
				Serial.print("Touch: C");
				Serial.println(i+1);
			}
		}
	}
	delay(50);
}

