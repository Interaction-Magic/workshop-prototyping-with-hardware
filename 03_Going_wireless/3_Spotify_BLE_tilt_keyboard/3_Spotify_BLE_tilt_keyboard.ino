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

// Install the library "Adafruit LSM6DS" by Adafruit
#include <Adafruit_LSM6DS3TRC.h>

Adafruit_LSM6DS3TRC lsm6ds3trc; // Reference to accelerometer chip 
float accel_y;              	  // Variables for acceleration

const float threshold_reset = 2;
const float threshold_trigger = 7;

bool is_reset = false;      // This false & true combo means we wait for the
bool was_triggered = true;  // board to level before triggering first time

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
	Keyboard.begin("SpotifyKeys");

	// Wait until we have BT connection to proceed
	Serial.print("Waiting to connect");
	while(!Keyboard.isConnected()){ 
		Serial.print(".");
		delay(100);
	};

	delay(1000);//just in case
	Serial.println("BT Connected!");

	// Initialise the accelerometer
	lsm6ds3trc.begin_I2C();

}

void loop() {

	// Fetch the data from the accelerometer and save current X/Y/Z values
	sensors_event_t accel, gyro, temp;
	lsm6ds3trc.getEvent(&accel, &gyro, &temp);
	accel_y = accel.acceleration.y;

	// If already triggered and now back below the threshold for resetting
	if(was_triggered && (abs(accel_y) <= threshold_reset)){
		is_reset = true;
		was_triggered = false;
	}

	// We have reset, but not triggered again yet
	if(is_reset && !was_triggered){

		// Passed threshold for positive direction trigger
		if(accel_y >= threshold_trigger){

			was_triggered = true;
			// On a Mac use KEY_LEFT_GUI instead of KEY_LEFT_CTRL
			Keyboard.press(KEY_LEFT_CTRL);
			Keyboard.press(KEY_RIGHT_ARROW);
			Keyboard.releaseAll();

		// Passed threshold for negative direction trigger
		}else if(accel_y <= -threshold_trigger){

			was_triggered = true;
			// On a Mac use KEY_LEFT_GUI instead of KEY_LEFT_CTRL
			Keyboard.press(KEY_LEFT_CTRL);
			Keyboard.press(KEY_LEFT_ARROW);
			Keyboard.releaseAll();

		}

	}
}
