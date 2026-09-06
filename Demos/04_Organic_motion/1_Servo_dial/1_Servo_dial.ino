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
const int dial_pin = A0;

const int min_dial = 0;
const int max_dial = 940;

void setup() {
	Serial.begin(9600);

	// Attach the servo motor to the pin
	motor1.attach(motor1_pin);
}

void loop() {
	// Clamp the dial value to 0 -> 940 value
	int dial = analogRead(dial_pin);
	dial = constrain(dial, min_dial, max_dial);

	// Scale dial value to 0 -> 180 for the servo
	int motor_position = map(dial, min_dial, max_dial, 0, 180);

	// Set servo value
	motor1.write(motor_position);
	delay(10);
}