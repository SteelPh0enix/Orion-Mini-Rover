#pragma once
#include <stdint.h>
#include <L298_motor_driver.hpp>
#include <chassis_driver.hpp>

class OrionMini {
 public:
  // Constants
  enum class Arm : int8_t {
    None = -1,
    Turntable = 0,
    Shoulder = 1,
    Forearm = 2,
    Wrist = 3,
    Cramp = 4
  };

  OrionMini();
  void initialize();
  bool initialized() const;

  void set_driving_speed(int speed, int rotation);
  void set_arm_motor_speed(Arm motor, int speed);

 private:
  constexpr static double PivotLimit{35.};
  bool m_initialized{false};

  ChassisDriver m_chassis{};
  L298MotorDriver m_arm[5]{};
};