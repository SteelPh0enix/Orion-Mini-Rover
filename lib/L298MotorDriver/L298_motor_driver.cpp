#include "L298_motor_driver.hpp"
#include <Arduino.h>

L298MotorDriver::L298MotorDriver(unsigned dir_left, unsigned dir_right,
                                 unsigned pwm, bool init) {
  set_pins(dir_left, dir_right, pwm);
  if (init) initialize();
}

bool L298MotorDriver::initialize() {
  if (!pins_set()) return false;

  pinMode(m_dir_left, OUTPUT);
  pinMode(m_dir_right, OUTPUT);
  pinMode(m_pwm, OUTPUT);

  m_initialized = true;
  return true;
}

void L298MotorDriver::set_pins(unsigned dir_left, unsigned dir_right,
                               unsigned pwm) {
  m_dir_left = dir_left;
  m_dir_right = dir_right;
  m_pwm = pwm;
  m_pins_set = true;
}

void L298MotorDriver::set_direction(bool direction) {
  if (direction) {  // right
    digitalWrite(m_dir_left, 0);
    digitalWrite(m_dir_right, 1);
  } else {  // left
    digitalWrite(m_dir_left, 1);
    digitalWrite(m_dir_right, 0);
  }
}

void L298MotorDriver::set_speed(int speed) {
  if (!initialized()) return;

  speed = constrain(speed, -PWM_MAX_VALUE, PWM_MAX_VALUE);
  m_speed = speed;

  set_direction(direction());

  if (speed < 0) speed *= -1;
  analogWrite(m_pwm, speed);
}

void L298MotorDriver::reverse_direction() {
  m_speed *= -1;
  set_direction(direction());
}

int L298MotorDriver::speed() const { return m_speed; }
bool L298MotorDriver::direction() const { return m_speed > 0; }