#pragma once
#include "../Module/module.hpp"

class L298MotorDriver : public ArduinoModule {
 public:
  L298MotorDriver() = default;
  L298MotorDriver(unsigned dir_left, unsigned dir_right, unsigned pwm,
                  bool init = true);

  virtual bool initialize() override;
  void set_pins(unsigned dir_left, unsigned dir_right, unsigned pwm);

  void set_speed(int speed);
  // 0 - left, 1 - right
  void set_direction(bool direction);
  void reverse_direction();

  int speed() const;
  // 1 - right, 0 - left
  bool direction() const;

 private:
  unsigned m_dir_left{};
  unsigned m_dir_right{};
  unsigned m_pwm{};

  unsigned m_speed{};
};
