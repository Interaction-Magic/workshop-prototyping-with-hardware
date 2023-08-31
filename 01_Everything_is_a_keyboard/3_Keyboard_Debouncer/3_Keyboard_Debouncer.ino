/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// Install this library manually from here:
// https://github.com/cyborg5/TinyUSB_Mouse_and_Keyboard
#include <TinyUSB_Mouse_and_Keyboard.h>

// Install the Bounce2 library by Thomas O Fredericks
#include <Bounce2.h>

// Create a new button
Bounce button = Bounce();

void setup() {

	// ⚠️ Safety stop!
	// Program will not begin when pin A0 connected to GND
	pinMode(A0, INPUT_PULLUP);
	while(digitalRead(A0) == LOW){
		delay(500);
	}

	// Attach pins A3 to the debouncers for use
	button.attach(A3,INPUT_PULLUP);

	// Start Arduino acting as a keyboard
	Keyboard.begin();
}

void loop() {

	// Update the debouncer as fast as possible
	button.update();

	// Check if button was pushed
	if(button.rose()) { 
		Keyboard.write(KEY_LEFT_ARROW);
	}
}
