# Workshops: Prototyping with Hardware and the Web

This repo contains all of the Arduino demo code for the workshops.

## Codepen for JS/HTML

For the `Remote control` module, we'll use [Codepen](https://codepen.io) for the Javascript parts of the course.

You can access all the links in [the collection here](https://codepen.io/collection/ZQOrxg). Here are the direct links to each demo:

+ [0/ Javascript intro](https://codepen.io/interactionmagic/pen/ogjrObG)
+ [1/ Reading from Arduino](https://codepen.io/interactionmagic/pen/wBKLNEJ)
+ [2/ Sending to Arduino](https://codepen.io/interactionmagic/pen/OPyedKm)
+ [3/ Sending any RGB colour](https://codepen.io/interactionmagic/pen/KwdjEpB)
+ [4/ Talking over Bluetooth](https://codepen.io/interactionmagic/pen/EaVBMOP) 
+ [5/ Bluetooth - all messages](https://codepen.io/interactionmagic/pen/ogjrOZp)
+ [6/ Serial - all messages](https://codepen.io/interactionmagic/pen/MYaMRmy)

## Links and sources

Collection of useful links and resources from the workshops:

### Adafruit Feather nRF52840 Sense

+ [Adafruit Feather nRF52840 Sense overview](https://learn.adafruit.com/adafruit-feather-sense)
+ [How to setup Arduino IDE](https://www.notion.so/interactionmagic/Setting-up-the-Feather-Sense-nRF52840-258c2b2e147080aeb761c8a7c4a26bb8)
+ [Full guide to the nRF52840 Sense](https://learn.adafruit.com/adafruit-feather-sense/overview)

### Libraries

+ [TinyUSB Mouse & Keyboard library](https://github.com/cyborg5/TinyUSB_Mouse_and_Keyboard)
+ [BLE Mouse & Keyboard library](https://github.com/cyborg5/BLE52_Mouse_and_Keyboard)

### Keyboard control
+ [Keyboard modifiers (esc, alt, arrows)](https://docs.arduino.cc/language-reference/en/functions/usb/Keyboard/keyboardModifiers/)
+ [Keyboad tester](https://keyboard-tester.com/)

### Capacitive touch

+ [Capacitive touch - simple](https://learn.adafruit.com/adafruit-capacitive-touch-sensor-breakouts/overview)
+ [Capacitive touch - I2C (better)](https://learn.adafruit.com/adafruit-cap1188-breakout/overview)
+ [Touch ideas](https://cdn-shop.adafruit.com/datasheets/HandcraftingSensors.pdf)
+ [DIY fabric sensor ideas](https://www.kobakant.at/DIY/)


### Design references

+ [Vehicle HMI](https://www.hmi.gallery/)
+ [Zoom off switch twitter video](https://twitter.com/lanewinfield/status/1339257875034566656)

### Bluetooth Keyboards

+ [Battery measurement on Feather Sense](https://learn.adafruit.com/adafruit-feather-sense/power-management)

### Javascript - WebSerial

+ [javascript.info](https://javascript.info/)
+ [CanIUse.com - Web Serial](https://caniuse.com/web-serial)
+ [Chrome device log](chrome://device-log/?refresh=2)
+ [List of USB IDs](http://www.linux-usb.org/usb.ids)

### Javascript - WebBluetooth

+ [Bluetooth Bell demo](https://tinyurl.com/bluetooth-bell)
+ [Casio Watch prototyper](https://casio-watch.netlify.app/)
+ [CanIUse.com Web Bluetooth](https://caniuse.com/web-bluetooth)
+ [Intro to BLE and GATT](https://learn.adafruit.com/introduction-to-bluetooth-low-energy/gatt)
+ [Chrome blog, Web Bluetooth and JS](https://developer.chrome.com/articles/bluetooth/)
+ [Adafruit nrf52 Bluefruit learning guide](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide)
+ [Apple BLE advertising guidelines](https://developer.apple.com/library/archive/qa/qa1931/_index.html)

## Debugging problems

+ [Using the older IDE](https://forum.seeedstudio.com/t/unable-to-use-latest-arduino-ide-with-nrf52840/269515/10)
+ Accelerometer chip changed! -> from `#include <Adafruit_LSM6DS33.h>` to `#include <Adafruit_LSM6DS3TRC.h>`