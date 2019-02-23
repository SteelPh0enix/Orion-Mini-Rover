#include <Arduino.h>
#include <constants.hpp>
#include <receiver.hpp>

Receiver comms;
char buffer[200];

void setup() {
  comms.initialize();
  Serial.begin(128000);
}

void loop() {
  comms.read_data(buffer);
  if (strlen(buffer) > 0) Serial.println(buffer);
}
