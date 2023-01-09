/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// Include this for Serial to work. You do NOT need to install any libraries for this
#include <Adafruit_TinyUSB.h>

// Install this library manually from here:
// https://github.com/cyborg5/TinyUSB_Mouse_and_Keyboard
#include <TinyUSB_Mouse_and_Keyboard.h>

// Install the library "Adafruit LSM6DS" by Adafruit
#include <Adafruit_LSM6DS33.h>

Adafruit_LSM6DS33 lsm6ds33; // Reference to accelerometer chip 
float accel_y;              // Variables for acceleration

const float threshold_reset = 2;
const float threshold_trigger = 7;

bool is_reset = false;      // This false & true combo means we wait for the
bool was_triggered = true;  // board to level before triggering first time

void setup() {

  // Start Arduino acting as a keyboard
  Keyboard.begin();

  // Initialise the accelerometer
  lsm6ds33.begin_I2C();
  
  // ⚠️ Safety stop!
  // Unless pin A0 is connected to GND, the program will not run
  // Red LED will flash to let you know something is wrong.
  pinMode(A0, INPUT_PULLUP);
  while(digitalRead(A0) == HIGH){
    digitalWrite(LED_BUILTIN, HIGH); delay(400);
    digitalWrite(LED_BUILTIN, LOW);  delay(200);
  }

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
  }

  // We have reset, but not triggered again yet
  if(is_reset && !was_triggered){

    // Passed threshold for positive direction trigger
    if(accel_y >= threshold_trigger){

      was_triggered = true;
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_RIGHT_ARROW);
      Keyboard.releaseAll();

    // Passed threshold for negative direction trigger
    }else if(accel_y <= -threshold_trigger){

      was_triggered = true;
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ARROW);
      Keyboard.releaseAll();

    }

  }
}
