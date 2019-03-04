#include "orion_mini.hpp"
#include <Arduino.h>
#include "../../include/pinout.hpp"

OrionMini::OrionMini() {
  m_chassis.set_pins(Pin::Chassis::Direction::Left,
                     Pin::Chassis::Direction::Right, Pin::Chassis::PWM::Left,
                     Pin::Chassis::PWM::Right);

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

  // This constrains power to 0:180 and extends it to 0:250, where 250 is max
  // PWM power
  int drive_power =
      map(constrain(sqrt(pow(rotation, 2) + pow(speed, 2)), 0, 180), 0, 180, 0,
          250);

  // Calculate angle of velocity vector
  double angle = atan2(speed, rotation);
  int direction = (speed >= 0 ? 1 : -1);
  int left_wheels_speed{drive_power * direction};
  int right_wheels_speed{drive_power * direction};

  if (angle > M_PI / 2.) {
    // II ćwiartka
    left_wheels_speed *= cos((angle - (M_PI / 2.)) * 2.);  // OK
    // Serial.print("II (L = ");
    // Serial.print(left_wheels_speed);
    // Serial.print("): ");
    // Serial.println(cos((angle - (M_PI / 2.)) * 2.));
  } else if (angle >= 0) {
    // I ćwiartka
    right_wheels_speed *= -cos(angle * 2.);  // OK
    // Serial.print("I (R = ");
    // Serial.print(right_wheels_speed);
    // Serial.print("): ");
    // Serial.println(-cos(angle * 2.));
  } else if (angle > -(M_PI / 2.)) {
    // IV ćwiartka
    left_wheels_speed *= -cos(angle * 2.);  // OK
    // Serial.print("IV (L = ");
    // Serial.print(left_wheels_speed);
    // Serial.print("): ");
    // Serial.println(-cos(angle * 2.));
  } else {
    // III ćwiartka
    right_wheels_speed *= cos((angle + (M_PI / 2.)) * 2.);  // OK
    // Serial.print("III (R = ");
    // Serial.print(right_wheels_speed);
    // Serial.print("): ");
    // Serial.println(cos((angle + (M_PI / 2.)) * 2.));
  }

  // Serial.print("rotation: ");
  // Serial.print(rotation);
  // Serial.print(", speed: ");
  // Serial.print(speed);
  // Serial.print(", power: ");
  // Serial.print(drive_power);
  // Serial.print(", angle: ");
  // Serial.println(angle);
  // Serial.println(M_PI / 2.);
  // Serial.print(", L: ");
  // Serial.print(left_wheels_speed);
  // Serial.print(", R: ");
  // Serial.println(right_wheels_speed);

  m_chassis.set_speed(left_wheels_speed, right_wheels_speed);
}

void OrionMini::set_arm_motor_speed(Arm motor, int speed) {
  if (!initialized() || motor == Arm::None) return;

  m_arm[static_cast<uint8_t>(motor)].set_speed(speed);
}