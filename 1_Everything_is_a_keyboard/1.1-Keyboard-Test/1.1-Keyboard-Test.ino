/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// Install this library manually from here:
// https://github.com/cyborg5/TinyUSB_Mouse_and_Keyboard
#include <TinyUSB_Mouse_and_Keyboard.h>

void setup() {

  // Start Arduino acting as a keyboard
  Keyboard.begin();

  // Press then release a key
  Keyboard.press('X');      
  Keyboard.release('X');
  delay(500);

  // Send a single key (same as press/release)
  Keyboard.write('Y');      
  delay(500);

  // Send a whole string of text
  Keyboard.print(" - Test from Interaction Magic - ");      
  delay(500);

  // Hold down SHIFT key to make text all caps
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.print("hello1");
  Keyboard.releaseAll();
}

void loop() {
}
