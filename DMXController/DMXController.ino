// Author: Charlie Eichman <ceichman7@gmail.com>

#include <ArduinoRS485.h> // the ArduinoDMX library depends on ArduinoRS485
#include <ArduinoDMX.h>

const int pot_pin = A0;
const int switch_pin = 7;
const int universeSize = 2;

int pot_val;
int chan1_output;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(pot_pin, INPUT);
  pinMode(switch_pin, INPUT_PULLUP);

  //  initialize the DMX library with the universe size
  if (!DMX.begin(universeSize)) {
    Serial.println("Failed to initialize DMX!");
    while (1); // wait for ever
  }

}

void loop() {
  pot_val = analogRead(pot_pin);
  chan1_output = pot_val >> 2;

  Serial.print("Pot val: ");
  Serial.print(pot_val);
  Serial.print("  Mapped DMX val: ");
  Serial.println(chan1_output);
  delay(50);

  DMX.beginTransmission();
  if (digitalRead(switch_pin)) {
    DMX.write(1, chan1_output);
    DMX.write(2, 50);     // test value for fixture intensity
  }
  else {
    DMX.write(1, 0);
    DMX.write(2, 0);     // test value for fixture intensity
  }
  DMX.endTransmission();
  

}
