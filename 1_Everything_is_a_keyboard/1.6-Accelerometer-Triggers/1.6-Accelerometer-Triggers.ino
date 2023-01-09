/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// Include this for Serial to work. You do NOT need to install any libraries for this
#include <Adafruit_TinyUSB.h>

// Install the library "Adafruit LSM6DS" by Adafruit
#include <Adafruit_LSM6DS33.h>

Adafruit_LSM6DS33 lsm6ds33; // Reference to accelerometer chip 
float accel_y;              // Variables for acceleration

const float threshold_reset = 2;
const float threshold_trigger = 7;

bool is_reset = false;      // This false & true combo means we wait for the
bool was_triggered = true;  // board to level before triggering first time

void setup() {

  // Open the Serial port
  Serial.begin(115200);
  
  // Initialise the accelerometer
  lsm6ds33.begin_I2C();

}

void loop() {

  // Fetch the data from the accelerometer and save current X/Y/Z values
  sensors_event_t accel, gyro, temp;
  lsm6ds33.getEvent(&accel, &gyro, &temp);
  accel_y = accel.acceleration.y;

  // If already triggered and now back below the threshold for resetting
  if(was_triggered && (abs(accel_y) <= threshold_reset)){
      is_reset = true;
      was_triggered = false;
      Serial.println("Reset!");
  }

  // We have reset, but not triggered again yet
  if(is_reset && !was_triggered){

    // Passed threshold for positive direction trigger
    if(accel_y >= threshold_trigger){

      was_triggered = true;
      Serial.println("Skip forward!");

    // Passed threshold for negative direction trigger
    }else if(accel_y <= -threshold_trigger){

      was_triggered = true;
      Serial.println("Skip backward!");

    }

  }
}
