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

      auto turntable_speed = json.get<int>(JsonConstant::ArmTurntable);
      auto shoulder_speed = json.get<int>(JsonConstant::ArmShoulder);
      auto forearm_speed = json.get<int>(JsonConstant::ArmForearm);
      auto wrist_speed = json.get<int>(JsonConstant::ArmWrist);
      auto cramp_speed = json.get<int>(JsonConstant::ArmCramp);

      orion.set_arm_motor_speed(OrionMini::Arm::Turntable, turntable_speed);
      orion.set_arm_motor_speed(OrionMini::Arm::Shoulder, shoulder_speed);
      // orion.set_arm_motor_speed(OrionMini::Arm::Forearm, forearm_speed);
      // orion.set_arm_motor_speed(OrionMini::Arm::Wrist, wrist_speed);
      // orion.set_arm_motor_speed(OrionMini::Arm::Cramp, cramp_speed);
    }
    m_buffer.clear();
  } else {
    orion.set_driving_speed(0, 0);
    orion.set_arm_motor_speed(OrionMini::Arm::Turntable, 0);
    orion.set_arm_motor_speed(OrionMini::Arm::Shoulder, 0);
    orion.set_arm_motor_speed(OrionMini::Arm::Forearm, 0);
    orion.set_arm_motor_speed(OrionMini::Arm::Wrist, 0);
    orion.set_arm_motor_speed(OrionMini::Arm::Cramp, 0);
  }
}
