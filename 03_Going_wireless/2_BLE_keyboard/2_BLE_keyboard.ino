/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// Include this for Serial to work. You do NOT need to install any libraries for this
#include <Adafruit_TinyUSB.h>

// Install this library manually from here:
// https://github.com/cyborg5/BLE52_Mouse_and_Keyboard
#include <BLE52_Mouse_and_Keyboard.h>

const int pin_button = 7;   // Button marked "User SW" on Arduino

void setup() {

	// ⚠️ Safety stop!
	// Program will not begin when pin A0 connected to GND
	pinMode(A0, INPUT_PULLUP);
	while(digitalRead(A0) == LOW){
		delay(500);
	}

	// Begin Serial for debugging
	Serial.begin(9600);  

	// Start Arduino acting as a keyboard, name defines the Bluetooth device name
	Keyboard.begin("GeorgeKBD");

	// Wait until we have BT connection to proceed
	Serial.print("Waiting to connect");
	uint8_t i=0;
	while(! Keyboard.isConnected()) { 
		Serial.print(".");
    delay(100);
	};

	// Give it a chance to connect
	delay(1000);
	Serial.println("BT Connected!");

	// Setup push button to default as pulled high
	pinMode(pin_button, INPUT_PULLUP);

}

void loop() {
	// If button is pushed, print character 'a'
	if(digitalRead(pin_button) == LOW){
		Keyboard.write('a');
	}
	delay(10);
}
