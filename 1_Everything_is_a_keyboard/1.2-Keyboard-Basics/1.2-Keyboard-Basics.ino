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
  // Unless pin A0 is connected to GND, the program will not run
  // Red LED will flash to let you know something is wrong.
  pinMode(A0, INPUT_PULLUP);
  while(digitalRead(A0) == HIGH){
    digitalWrite(LED_BUILTIN, HIGH); delay(400);
    digitalWrite(LED_BUILTIN, LOW);  delay(200);
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
