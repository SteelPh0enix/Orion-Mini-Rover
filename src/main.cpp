#include <Arduino.h>
#include <ArduinoJson.hpp>
#include <constants.hpp>
#include <orion_mini.hpp>
#include <receiver.hpp>

OrionMini orion;
Receiver receiver;

char buffer[RoverConstants::BufferSize];
ArduinoJson::StaticJsonBuffer<RoverConstants::BufferSize> m_buffer{};

void setup() {
  Serial.begin(128000);
  orion.initialize();
  receiver.initialize();
  receiver.print_debug_data();
}

void loop() {
  if (receiver.read_data(buffer, RF24Constant::Timeout)) {
    ArduinoJson::JsonObject const& json = m_buffer.parseObject(buffer);
    if (json.success()) {
      auto speed = json.get<int>(JsonConstant::Speed);
      auto rotation = json.get<int>(JsonConstant::Turning);
      orion.set_driving_speed(
          (speed > -RoverConstants::DeadZone && speed < RoverConstants::DeadZone
               ? 0
               : speed),
          (rotation > -RoverConstants::DeadZone &&
                   rotation < RoverConstants::DeadZone
               ? 0
               : rotation));
    }
    m_buffer.clear();
  } else {
    orion.set_driving_speed(0, 0);
  }
}
