// Author: Charlie Eichman <ceichman7@gmail.com>

#include <ArduinoRS485.h> // the ArduinoDMX library depends on ArduinoRS485
#include <ArduinoDMX.h>

const int pot_pin = A0;
const int universeSize = 2;

int pot_val;
int chan1_output;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(pot_pin, INPUT);

    // initialize the DMX library with the universe size
  // if (!DMX.begin(universeSize)) {
  //   Serial.println("Failed to initialize DMX!");
  //   while (1); // wait for ever
  // }

}

void loop() {
  pot_val = analogRead(pot_pin);
  chan1_output = pot_val >> 2;

  Serial.print("Pot val: ");
  Serial.print(pot_val);
  Serial.print("  Mapped DMX val: ");
  Serial.println(chan1_output);
  delay(200);

  // DMX.beginTransmission();
  // DMX.write(1, chan1_output);
  // DMX.endTransmission();

}
