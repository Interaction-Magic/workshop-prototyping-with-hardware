/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// For Serial
#include <Adafruit_TinyUSB.h> 

int counter = 0;

void setup() {
	// Open the Serial port
	Serial.begin(9600);
}

void loop() {
	
	Serial.print("Hello! ");
	Serial.println(counter);
	counter++;

	delay(1000);
}
