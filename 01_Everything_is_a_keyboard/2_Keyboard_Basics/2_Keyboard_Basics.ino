/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// Install this library manually from here:
// https://github.com/cyborg5/TinyUSB_Mouse_and_Keyboard
#include <TinyUSB_Mouse_and_Keyboard.h>

const int pin_button = 7;   // Button marked "User SW" on Arduino

void setup() {

	// Start Arduino acting as a keyboard
	Keyboard.begin();

	// ⚠️ Safety stop!
	// Program will not begin when pin A0 connected to GND
	pinMode(A0, INPUT_PULLUP);
	while(digitalRead(A0) == LOW){
		delay(500);
	}

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
