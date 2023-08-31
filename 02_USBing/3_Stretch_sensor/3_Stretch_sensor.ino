/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// Create variables for pins
const int stretch_pin = A5;

// Set max and min levels for stretch detection
// You will need to calculate these yourself by testing the length of stretch wire that you have
// Then you can pick numbers that work for you
const int min_level = 370; // Set this a little bit higher than your minimum value
const int max_level = 490; // Set this a little bit lower than your minimum value

void setup() {
	Serial.begin(115200);
}

void loop() {
	// Read in stretch sensor value
	int stretch_reading = analogRead(stretch_pin);

	// You can uncomment the code below once you've set the min and max levels correctly

	// Constrain reading so that it doesn't exceed bounds
	// stretch_reading = constrain(stretch_reading, min_level, max_level);

	// Map the stretch sensor to 0 -> 100 range
	// int scaled = map(stretch_reading, min_level, max_level, 0, 100);

	Serial.println(scaled);
	delay(20);
}
