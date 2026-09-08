/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// Include this for Serial to work. You do NOT need to install any libraries for this
#include <Adafruit_TinyUSB.h>

// Install the "Adafruit CAP1188" library
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

  // Decrease sensitivity a little - default is 0x2F (32x) per datasheet
  // Uncomment one of these:

  //cap.writeRegister(CAP1188_SENSITIVITY, 0x3F);  // 16x sensitivity
  //cap.writeRegister(CAP1188_SENSITIVITY, 0x4F);  // 8x  sensitivity
  //cap.writeRegister(CAP1188_SENSITIVITY, 0x5F);  // 4x  sensitivity
  cap.writeRegister(CAP1188_SENSITIVITY, 0x6F);    // 2x  sensitivity
  //cap.writeRegister(CAP1188_SENSITIVITY, 0x7F);  // 1x  sensitivity

  // Write out sensitivity
  Serial.print("Sensitivity: 0x");
  Serial.println(cap.readRegister(CAP1188_SENSITIVITY), HEX);
}

void loop() {
	uint8_t touched = cap.touched();

	if (touched > 0) {
		// We detected a touch!

		for (uint8_t i=0; i<8; i++) {
			if (touched & (1 << i)) {
				Serial.print("Touch:");
				Serial.println(i+1);
			}
		}
	}
	delay(50);
}

