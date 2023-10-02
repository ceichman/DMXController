// Author: Charlotte Eichman <ceichman7@gmail.com>

#include <ArduinoRS485.h> // the ArduinoDMX library depends on ArduinoRS485
#include <ArduinoDMX.h>
#include <NumericalDisplay.h>

const int pot_pin = A0;
const int switch_pin = 13;
const int tempoMode_pin = 12;
const int tempoButton_pin = 11;
const int universeSize = 2;

const int intensity = 50;   // change to be controllable in future

int pot_val;
int chan1_output;
int flashDelay = 200;  // initial tempo delay
int lastClickTime = 0;
int nextFlashTime = flashDelay;

int lastButtonState;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(pot_pin, INPUT);
  pinMode(switch_pin, INPUT_PULLUP);
  pinMode(tempoMode_pin, INPUT_PULLUP);
  pinMode(tempoButton_pin, INPUT_PULLUP);

  //  initialize the DMX library with the universe size
  if (!DMX.begin(universeSize)) {
    Serial.println("Failed to initialize DMX!");
    while (1); // wait for ever
  }

}

void loop() {

  int tempoMode = digitalRead(tempoMode_pin);
  int now = millis();

  // Serial.print("Pot val: ");
  // Serial.print(pot_val);
  // Serial.print("  Mapped DMX val: ");
  // Serial.println(chan1_output);
  delay(50);

  DMX.beginTransmission();

  if (!digitalRead(switch_pin)) {
    if (digitalRead(tempoMode_pin)) {
      // normal mode
      pot_val = analogRead(pot_pin);
      chan1_output = pot_val >> 2;
      DMX.write(1, chan1_output);
      DMX.write(2, intensity);     // test value for fixture intensity
    }
    else {
      // tap tempo mode
      int buttonState = digitalRead(tempoButton_pin);
      if (now >= nextFlashTime) {
        // flash
        DMX.write(1, 10);
        DMX.write(2, intensity);
        nextFlashTime = now + flashDelay;
      }
      else {
        // don't flash
        DMX.write(1, 0);
        DMX.write(2, 0);
      }

      if (buttonState != lastButtonState) {    // if buttonState isn't what it just was,
        if (!buttonState) {    // if button has just been pressed,
          flashDelay = now - lastClickTime;    // set the delay time
          lastClickTime = now;              // reset last click time for next iteration
          DMX.write(1, 10);
          DMX.write(2, intensity);
          nextFlashTime = now + flashDelay;
        }
      }
      lastButtonState = buttonState;
    }

  }
  else {    // output disabled
    DMX.write(1, 0);
    DMX.write(2, 0);     
  }
  DMX.endTransmission();
  
}
