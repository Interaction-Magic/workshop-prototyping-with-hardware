/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// For Serial
#include <Adafruit_TinyUSB.h> 

// Servo library
#include <Servo.h>

// Create Servo object
Servo motor1;

const int motor1_pin = 5;

void setup() {
	Serial.begin(9600);

	// Attach the servo motor to the pin
	motor1.attach(motor1_pin);
}

void loop() {
	if (Serial.available() > 0) {
		// Read in bytes and convert to an angle
    	String input = Serial.readStringUntil('\n');
		int angle = input.toInt();
		
		// Constrain angle to valid servo range
		angle = constrain(angle, 0, 180);
		motor1.write(angle);
	}
}