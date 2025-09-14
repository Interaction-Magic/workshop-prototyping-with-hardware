/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// No need to install anything for this one
#include <bluefruit.h>

// For Serial
#include <Adafruit_TinyUSB.h> 

// Servo library
#include <Servo.h>

// Create Servo object
Servo motor1;
const int motor1_pin = 5;

// BLE UART service we will advertise
BLEUart bleuart;

void setup() {

	Serial.begin(9600);

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
	Bluefruit.setName("George-Servo-Demo");
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

		// Convert message to a number
		int servo_angle = atoi(receive_msg);

		// Constrain to 0->180, just in case data was bad
		servo_angle = constrain(servo_angle, 0, 180);

		// Set angle of servo
		motor1.write(servo_angle);
	}
}