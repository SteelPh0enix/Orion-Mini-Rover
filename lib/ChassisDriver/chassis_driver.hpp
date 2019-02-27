#pragma once
#include <module.hpp>

class ChassisDriver : public ArduinoModule {
 public:
  struct Speed {
    int left;
    int right;
  };

  ChassisDriver() = default;
  ChassisDriver(unsigned left_dir_pin, unsigned right_dir_pin,
                unsigned left_pwm, unsigned right_pwm, bool init = true);

  virtual bool initialize() override;

  void set_pins(unsigned left_dir_pin, unsigned right_dir_pin,
                unsigned left_pwm, unsigned right_pwm);

  void set_speed(int left_speed, int right_speed);
  void set_left_speed(int speed);
  void set_right_speed(int speed);

  Speed speed() const;
  int left_speed() const;
  int right_speed() const;

  void set_max_speed(int speed);
  void set_min_speed(int speed);

  int max_speed() const;
  int min_speed() const;

 private:
  unsigned m_left_dir_pin{};
  unsigned m_right_dir_pin{};
  unsigned m_left_pwm{};
  unsigned m_right_pwm{};

  int m_left_speed{};
  int m_right_speed{};

  int m_max_speed{PWM_MAX_VALUE};
  int m_min_speed{-PWM_MAX_VALUE};
};