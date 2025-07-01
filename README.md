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
1. When the IR sensor detects an object, the system registers a HIGH signal and increments the counter.
