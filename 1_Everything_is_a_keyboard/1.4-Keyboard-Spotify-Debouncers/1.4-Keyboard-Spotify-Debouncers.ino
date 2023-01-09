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

// Create three new buttons to control the music player
Bounce skip_backwards = Bounce();
Bounce play_pause = Bounce();
Bounce skip_forwards = Bounce();

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

  // Attach pins A3, A4 & A5 to the debouncers for use
  skip_backwards.attach(A3,INPUT_PULLUP);
  play_pause.attach(A4,INPUT_PULLUP);
  skip_forwards.attach(A5,INPUT_PULLUP);

}

void loop() {
  
  // Update the debouncers as fast as possible
  skip_backwards.update(); 
  play_pause.update(); 
  skip_forwards.update(); 

  // Check if buttons were pushed
  if(skip_backwards.rose()) { 
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.releaseAll();
  }
  if(play_pause.rose()) { 
    Keyboard.write(' ');
  }
  if(skip_forwards.rose()) { 
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_RIGHT_ARROW);
    Keyboard.releaseAll();
  }
}
