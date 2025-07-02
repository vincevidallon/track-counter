# Arduino Electronic Track Counter

This repository contains the source code for an electronic track counter built using an Arduino Uno and an IR sensor. The track counter is used to detect how many visitors cross a surveyed segment of a walking track with an IR beam, increments the count and then outputs this through an I2C LCD. It also provides optional serial output as well as trigger signalling.

## Features
- IR beam-based detection through digital input
- LCD display toggled via a power button
- Count reset via a reset button
- Trigger signal pulse output, showing a visual for the detection of a visitor
- Serial output of visitor counts for logging and debugging
- Debounced button handling for system reliability

## How It Works
** Object Detection **
When the IR sensor detects an object, the system registers a HIGH signal and increments the counter.

** Display Toggle **
Press the power button to toggle the LCD display between on or off. The count is still tracked even when the display is off.

** Reset Button **
When the reset button is pressed, the count is reset back to zero.

** Trigger Output **
When an object is detected, a brief 50ms HIGH signal is sent to the Arduino's pin 5 and the counter is incremented.

** Serial Output **
The visitor count is outputted to the serial monitor for logging/debugging.

## Required Libraries
- [hd44780 Library](https://docs.arduino.cc/libraries/hd44780/)
  Can install the library via the Library Manager in Arduino IDE.

# Authors
Vince Vidallon
Rebecca Connolly
Sarah Hermiston
*University of Canterbury - ENEL200 Track Counter Project*
