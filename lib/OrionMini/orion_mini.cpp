#include "orion_mini.hpp"
#include <Arduino.h>
#include "../../include/pinout.hpp"

OrionMini::OrionMini() {
  m_chassis.set_pins(Pin::Chassis::Direction::Left,
                     Pin::Chassis::Direction::Right, Pin::Chassis::PWM::Left,
                     Pin::Chassis::PWM::Right);

  m_chassis.set_max_speed(100);
  m_chassis.set_min_speed(0);

  m_arm[static_cast<uint8_t>(Arm::Turntable)].set_pins(
      Pin::Arm::Direction::TurntableLeft, Pin::Arm::Direction::TurntableRight,
      Pin::Arm::PWM::Turntable);

  m_arm[static_cast<uint8_t>(Arm::Shoulder)].set_pins(
      Pin::Arm::Direction::ShoulderDown, Pin::Arm::Direction::ShoulderUp,
      Pin::Arm::PWM::Shoulder);

  m_arm[static_cast<uint8_t>(Arm::Forearm)].set_pins(
      Pin::Arm::Direction::ForearmDown, Pin::Arm::Direction::ForearmUp,
      Pin::Arm::PWM::Forearm);

  m_arm[static_cast<uint8_t>(Arm::Wrist)].set_pins(
      Pin::Arm::Direction::WristDown, Pin::Arm::Direction::WristUp,
      Pin::Arm::PWM::Wrist);

  m_arm[static_cast<uint8_t>(Arm::Cramp)].set_pins(
      Pin::Arm::Direction::CrampRelease, Pin::Arm::Direction::CrampTighten,
      Pin::Arm::PWM::Cramp);
}

void OrionMini::initialize() {
  if (initialized()) return;
  m_chassis.initialize();
  m_arm[static_cast<uint8_t>(Arm::Turntable)].initialize();
  m_arm[static_cast<uint8_t>(Arm::Shoulder)].initialize();
  m_arm[static_cast<uint8_t>(Arm::Forearm)].initialize();
  m_arm[static_cast<uint8_t>(Arm::Wrist)].initialize();
  m_arm[static_cast<uint8_t>(Arm::Cramp)].initialize();
  m_initialized = true;
}

bool OrionMini::initialized() const { return m_initialized; }

void OrionMini::set_driving_speed(int speed, int rotation) {
  if (!initialized()) return;

  speed = map(speed, -180, 180, 0, 100);

  int speed_a = speed * (45 - rotation % 90) / 45;
  int speed_b = min(100, min(2 * speed + speed_a, 2 * speed - speed_a));

  if (rotation < -90) {
    m_chassis.set_speed(-speed_b, -speed_a);
  } else if (rotation < 0) {
    m_chassis.set_speed(-speed_a, speed_b);
  } else if (rotation < 90) {
    m_chassis.set_speed(speed_b, speed_a);
  } else {
    m_chassis.set_speed(speed_a, -speed_b);
  }
}

void OrionMini::set_arm_motor_speed(Arm motor, int speed) {
  if (!initialized() || motor == Arm::None) return;

  m_arm[static_cast<uint8_t>(motor)].set_speed(speed);
}