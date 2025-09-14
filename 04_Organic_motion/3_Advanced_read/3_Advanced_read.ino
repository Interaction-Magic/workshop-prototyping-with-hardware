/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// No need to install anything for this one
#include <bluefruit.h>

// For Serial
#include <Adafruit_TinyUSB.h> 

// Include Adafruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// Servo library
#include <Servo.h>

// RGB LED bits
const int rgb_pin = 8; 	// Pin for RGB LED
const int num_leds = 1; // Number of RGB LEDs we have
Adafruit_NeoPixel strip(num_leds, rgb_pin, NEO_GRB + NEO_KHZ800);

// Create Servo object
Servo motor1;
const int motor1_pin = 5;

// BLE UART service we will advertise
BLEUart bleuart;

void setup() {

  	Serial.begin(9600);

	// Setup RGB LED and make LED white
	strip.begin();
	strip.setPixelColor(0, 0xFFFFFF);
	strip.show();

	// Attach the servo motor to the pin
	motor1.attach(motor1_pin);

	// /////////////////////////////////////
	// Rest of this is Bluetooth setup...

	Bluefruit.autoConnLed(true);  // Set BLE LED to be enabled on CONNECT
	Bluefruit.configPrphBandwidth(BANDWIDTH_MAX); // Config the peripheral connection with max bandwidth 

	Bluefruit.begin();			// Setup and begin connection
	Bluefruit.setTxPower(4); 	// Check bluefruit.h for supported values

	// Set the name the device will be advertised as
	// For some reason, we need to call getName() afterwards to force the name to set
	Bluefruit.setName("George-Advanced-Demo");
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

// Create a buffer to store incoming message in
const byte msg_length = 64;
char receive_msg[msg_length];	// For receiving BLE UART message
int counter = 0;

void loop() {

	// Check for message from Bluetooth
	while(bleuart.available()){
		// Read in next character to message buffer
		char character = bleuart.read();
		receive_msg[counter] = character;
		counter++;

		// Check so we don't overflow the length of the buffer
		if(counter >= msg_length){
			counter = msg_length - 1;
		}
	}

	// If we received a message, process it
	if(counter > 0){
		receive_msg[counter] = '\0'; // Terminate the string
		counter = 0;

		Serial.print("Received: ");
		Serial.print(receive_msg);
		Serial.print(" [");
		Serial.print(strlen(receive_msg));
		Serial.println("]");

		// Decide what to do with the message based on the first character (the option)
		// Rest of the message is the parameters

		char option = receive_msg[0];
		char *parameters = &receive_msg[1];
		uint8_t parameters_length = strlen(parameters);

		if(option == 's'){

			// Set servo angle
			int servo_angle = atoi(parameters);
			servo_angle = constrain(servo_angle, 0, 180);
			motor1.write(servo_angle);
			
		}else if(option == 'p'){

			// Set a chosen, primary colour for LED

			if(parameters[0] == 'r'){

				// Set LED to Red
				strip.setPixelColor(0, 0xFF0000);
				strip.show();

			}else if(parameters[0] == 'g'){
				
				// Set LED to green
				strip.setPixelColor(0, 0x00FF00);
				strip.show();

			}

		}else if(option == 'c'){

			// Set a custom colour for LED

			if(strlen(parameters) == 6){
				// We expected a hex colour with 6 characters in it

				// Set the colour
				strip.setPixelColor(0, str2col(parameters));
				strip.show();
			}

		}
	}
}



// This function converts a string of text that is a hex colour (e.g. FF00AC) into a
// number that can be used to set the LED PixelColor
uint32_t str2col(char* args){

	return 	(char2hex(args[0])<<20) +
				(char2hex(args[1])<<16) +
				(char2hex(args[2])<<12) +
				(char2hex(args[3])<<8) +
				(char2hex(args[4])<<4) +
				char2hex(args[5]);
}

// Return int value from a hex character 0-9,A-F
uint8_t char2hex(char c){
	uint16_t i = (uint16_t)c;
	if(isHexadecimalDigit(c)){
		return (i > '9')? (i &~ 0x20) - 'A' + 10: (i - '0');
	}
	return 0;
}