/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// For Serial
#include <Adafruit_TinyUSB.h> 

// Include Adafruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// RGB LED bits
const int rgb_pin = 8; 	// Pin for RGB LED
const int num_leds = 1; // Number of RGB LEDs we have
Adafruit_NeoPixel strip(num_leds, rgb_pin, NEO_GRB + NEO_KHZ800);

void setup() {

	// Setup RGB LED and make LED white
	strip.begin();
	strip.setPixelColor(0, 0xFFFFFF);
	strip.setBrightness(127); // Set half brightness
	strip.show();

	// Open the Serial port
	Serial.begin(9600);
	
}

void loop() {
	if (Serial.available()) {
		char msg = Serial.read();
		
		if (msg == 'r') {
			// Set LED to Red
			strip.setPixelColor(0, 0xFF0000);
			strip.show();
		}else if (msg == 'g') {
			// Set LED to green
			strip.setPixelColor(0, 0x00FF00);
			strip.show();
		}
	}
}