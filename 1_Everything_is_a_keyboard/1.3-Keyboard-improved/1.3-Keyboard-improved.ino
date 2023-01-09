/*
 * ©️2023 Interaction Magic - George Cave
 * Workshop: Prototyping with hardware and the web
 * https://interactionmagic.com
 */

// Install this library manually from here:
// https://github.com/cyborg5/TinyUSB_Mouse_and_Keyboard
#include <TinyUSB_Mouse_and_Keyboard.h>

// Small structure to save information about our keyboard buttons
struct keyboard_button{
   int pin;
   int key;
   bool last_state;
};

const int num_buttons = 3;

// Here we define all of our keyboard buttons and the pins they connect to 
keyboard_button buttons[num_buttons] = {
  {7, 'a', HIGH},
  {5, 'b', HIGH},
  {6, 'c', HIGH},
};

void setup() {

  // Start Arduino acting as a keyboard
  Keyboard.begin();

  // ⚠️ Safety stop!
  // Unless pin A0 is connected to GND, the program will not run
  // Red LED will flash to let you know something is wrong.
  pinMode(A0, INPUT_PULLUP);
  while(digitalRead(A0) == HIGH){
    digitalWrite(LED_BUILTIN, HIGH); delay(300);
    digitalWrite(LED_BUILTIN, LOW);  delay(50);
  }

  // Set push button pin
  for(int i=0; i<num_buttons; i++){
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }

}

void loop() {

   // Loop for each button
   for(int i=0; i<num_buttons; i++){
      if( (buttons[i].last_state==LOW) && (digitalRead(buttons[i].pin)==HIGH) ){
         // If last state was pressed and now it is released, write character
         Keyboard.write(buttons[i].key);
      }
      // Save last state of button
      buttons[i].last_state = digitalRead(buttons[i].pin);
   }

}
