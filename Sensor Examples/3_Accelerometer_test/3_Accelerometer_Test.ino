/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// Include this for Serial to work. You do NOT need to install any libraries for this
#include <Adafruit_TinyUSB.h>

// Install the library "Adafruit LSM6DS" by Adafruit
#include <Adafruit_LSM6DS3TRC.h>

Adafruit_LSM6DS3TRC lsm6ds3trc;   // Reference to accelerometer chip 
float accel_x, accel_y, accel_z;  // Variables for acceleration in X/Y/Z

void setup() {

	// Open the Serial port
	Serial.begin(115200);

	// Initialise the accelerometer
	lsm6ds3trc.begin_I2C();

}

void loop() {

	// Fetch the data from the accelerometer and save current X/Y/Z values
	sensors_event_t accel, gyro, temp;
	lsm6ds3trc.getEvent(&accel, &gyro, &temp);
	accel_x = accel.acceleration.x;
	accel_y = accel.acceleration.y;
	accel_z = accel.acceleration.z;

	// Debug all acceleration values
	Serial.print("X:");
	Serial.print(accel_x);
	Serial.print(" Y:");
	Serial.print(accel_y);
	Serial.print(" Z:");
	Serial.print(accel_z);
	//Serial.print(" min:-12 max:12"); // Uncomment this line to stabalise graph (Serial Plotter)
	Serial.println(" m/s^2");
}
