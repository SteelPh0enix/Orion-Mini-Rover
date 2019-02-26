#include "chassis_driver.hpp"
#include <Arduino.h>

ChassisDriver::ChassisDriver(unsigned left_dir_pin, unsigned right_dir_pin,
                             unsigned left_pwm, unsigned right_pwm, bool init) {
  set_pins(left_dir_pin, right_dir_pin, left_pwm, right_pwm);
  if (init) initialize();
}

void ChassisDriver::set_pins(unsigned left_dir_pin, unsigned right_dir_pin,
                             unsigned left_pwm, unsigned right_pwm) {
  m_left_dir_pin = left_dir_pin;
  m_right_dir_pin = right_dir_pin;
  m_left_pwm = left_pwm;
  m_right_pwm = right_pwm;
  m_pins_set = true;
}

bool ChassisDriver::initialize() {
  if (!pins_set()) return false;

  pinMode(m_left_dir_pin, OUTPUT);
  pinMode(m_right_dir_pin, OUTPUT);
  pinMode(m_left_pwm, OUTPUT);
  pinMode(m_right_pwm, OUTPUT);

  m_initialized = true;
  return true;
}

void ChassisDriver::set_speed(int left_speed, int right_speed) {
  set_left_speed(left_speed);
  set_right_speed(right_speed);
}

void ChassisDriver::set_left_speed(int speed) {
  if (!initialized()) return;

  speed = constrain(speed, -PWM_MAX_VALUE, PWM_MAX_VALUE);
  m_left_speed = speed;

  digitalWrite(m_left_dir_pin, speed < 0);
  if (speed < 0) speed *= -1;
  analogWrite(m_left_pwm, speed);
}

void ChassisDriver::set_right_speed(int speed) {
  if (!initialized()) return;

  speed = constrain(speed, -PWM_MAX_VALUE, PWM_MAX_VALUE);
  m_right_speed = speed;

  digitalWrite(m_right_dir_pin, speed < 0);
  if (speed < 0) speed *= -1;
  analogWrite(m_right_pwm, speed);
}

ChassisDriver::Speed ChassisDriver::speed() const {
  return {left_speed(), right_speed()};
}

int ChassisDriver::left_speed() const { return m_left_speed; }

int ChassisDriver::right_speed() const { return m_right_speed; }