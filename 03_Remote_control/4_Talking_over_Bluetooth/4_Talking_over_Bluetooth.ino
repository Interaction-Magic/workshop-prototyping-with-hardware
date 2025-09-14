/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 * 
 * Updated to use BluetoothManager class
 */

// Include the Bluetooth manager
#include "BluetoothUART.h"

// Include Adafruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// Install the Bounce2 library by Thomas O Fredericks
#include <Bounce2.h>

// Create a new button
Bounce button = Bounce();

// RGB LED bits
const int rgb_pin = 8;      // Pin for RGB LED
const int num_leds = 1;     // Number of RGB LEDs we have
Adafruit_NeoPixel strip(num_leds, rgb_pin, NEO_GRB + NEO_KHZ800);

// Create Bluetooth UART instance
BluetoothUART bluetooth;

void setup() {
	// Setup RGB LED and make LED white
	strip.begin();
	strip.setPixelColor(0, 0xFFFFFF);
	strip.show();

	// Button marked "User SW" on Arduino
	button.attach(7,INPUT_PULLUP);

	// Initialize Bluetooth with device name
	bluetooth.connect("George-Demo");
}

void loop() {
	
   // Check for button push
	button.update();
	if(button.fell()) { 
		bluetooth.send("press!");
	}else if(button.rose()){
		bluetooth.send("release!");
	}

	// Check for message from computer
	while(bluetooth.available()){
		uint8_t msg = bluetooth.read();
		
		if(msg == 'r'){
			// Set LED to Red
			strip.setPixelColor(0, 0xFF0000);
			strip.show();
		}
		else if(msg == 'g'){
			// Set LED to green
			strip.setPixelColor(0, 0x00FF00);
			strip.show();
		}
	}
}