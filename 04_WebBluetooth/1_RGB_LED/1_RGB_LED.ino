/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// No need to install anything for this one
#include <bluefruit.h>

// Include Adafruit NeoPixel library
#include <Adafruit_NeoPixel.h>

const int pin_button = 7;   // Button marked "User SW" on Arduino

// RGB LED bits
const int rgb_pin = 8; 	// Pin for RGB LED
const int num_leds = 1; // Number of RGB LEDs we have
Adafruit_NeoPixel strip(num_leds, rgb_pin, NEO_GRB + NEO_KHZ800);

// BLE UART service we will advertise
BLEUart bleuart;

void setup() {

	// Setup RGB LED and make LED white
	strip.begin();
	strip.setPixelColor(0, 0xFFFFFF);
	strip.show();

	// Setup push button to default as pulled high
	pinMode(pin_button, INPUT_PULLUP);

	// /////////////////////////////////////
	// Rest of this is Bluetooth setup...

	Bluefruit.autoConnLed(true);  // Set BLE LED to be enabled on CONNECT
	Bluefruit.configPrphBandwidth(BANDWIDTH_MAX); // Config the peripheral connection with max bandwidth 

	Bluefruit.begin();			// Setup and begin connection
	Bluefruit.setTxPower(4); 	// Check bluefruit.h for supported values

	// Set the name the device will be advertised as
	// For some reason, we need to call getName() afterwards to force the name to set
	Bluefruit.setName("George-RGB-Demo");
	char fetchedName[64];
	Bluefruit.getName(fetchedName, 64);
	
	// Configure and Start BLE Uart Service
	bleuart.begin(); 

	// Set up and start advertising
	Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
	Bluefruit.Advertising.addTxPower();

	// Include bleuart 128-bit uuid
	Bluefruit.Advertising.addService(bleuart);

	Bluefruit.ScanResponse.addName();

	// Start advertising based on Apple recommended intervals:
	Bluefruit.Advertising.restartOnDisconnect(true);
	Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
	Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
	Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
}

void loop() {

	// Check for button push
	if(digitalRead(pin_button) == LOW){

		char button_msg[] = "push!";	
		bleuart.write(button_msg, strlen(button_msg));

	}

	// Check for message from computer
	while(bleuart.available()){
		byte msg;
		msg = (byte) bleuart.read();
		if(msg == 'r'){

			// Set LED to Red
			strip.setPixelColor(0, 0xFF0000);
			strip.show();

		}else if(msg == 'g'){
			
			// Set LED to green
			strip.setPixelColor(0, 0x00FF00);
			strip.show();

		}
	}
}