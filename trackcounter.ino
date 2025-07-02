#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;


// *** Configuration for I/O pins ***
const int ioPinSensor = A0;  // Using A0 as the sensor input
const int ioPowerButton = 2;
const int ioResetButton = 3; 
const int ioDigitalIR = 7;
const int ioLedPin = 13;
const int ioTriggerPin = 5;

const int UPDATE_INTERVAL_MSEC = 100; 
const uint32_t BAUD_RATE = 115200;
const float DISTANCE_THRESHOLD_VOLTAGE = 0.75;

// Global variables
bool counted = false;
bool displayOn = false;              // Current display state
int lastPowerButtonState = HIGH;     // Previous power button state
int visitorCount = 0;
bool isAboveThreshold = true;     

// *** Utility functions ***
float adcCodeToVoltage(int adcCode) {
  return (adcCode * (5.0 / 1024));
}


void sendSensorVoltage(float sensorVoltage) {
  Serial.print("Sensor Voltage: ");
  Serial.println(sensorVoltage);
}


void sendCount(int count) {
  Serial.print("Count: ");
  Serial.println(count);
}

// *** Display functions ***
void updateLCD() {
  lcd.clear();
  lcd.print("Count: ");
  lcd.print(visitorCount);
}

void toggleDisplay() {
  displayOn = !displayOn;
  if (displayOn) {
    lcd.on();
    lcd.clear();
    lcd.print("Display ON");
    delay(1000);
    updateLCD();
  }
  else {
    lcd.off();
  }
}

// *** Counting visitor logic ***
void checkVisitorTrigger() {
  if (!counted && digitalRead(ioDigitalIR == HIGH)) {
    visitorCount++;
    sendCount(visitorCount);
    isAboveThreshold = false;
    counted = true;
  }

  // *** Trigger output signal ***
  digitalWrite(ioTriggerPin, HIGH);
  delay(50);
  digitalWrite(ioTriggerPin, LOW);

  if (displayOn) {
    updateLCD();
  }
  else if (digitalRead(ioDigitalIR) == LOW) {
    counted = false;
  }
}

// *** Reset Button Logic ***
void checkResetButton() {
  if (digitalRead(ioResetButton) == LOW) {
    visitorCount = 0;
  }
  if (displayOn) {
    updateLCD();
  }
  delay(50);
}

// *** Setup ***
void setup() {
  pinMode(ioPowerButton, INPUT_PULLUP);
  pinMode(ioResetButton, INPUT_PULLUP);
  pinMode(ioDigitalIR, INPUT);
  pinMode(ioLedPin, OUTPUT);
  pinMode(ioTriggerPin, OUTPUT);
  digitalWrite(ioLedPin, LOW);

  // *** Serial and LCD Setup ***
  Serial.begin(BAUD_RATE);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.off();  // Start with LCD off
}


// *** Main Loop ***
void loop() {
  // Power Button - trigger LCD on rising edge
  int powerButtonState = digitalRead(ioPowerButton);
  if (powerButtonState == LOW && lastPowerButtonState == HIGH) {
    toggleDisplay();
    delay(50);
  }
  lastPowerButtonState = powerButtonState;

  checkVisitorTrigger();
  checkResetButton();

  delay(UPDATE_INTERVAL_MSEC);
}
