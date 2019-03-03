// Various constants used in program, shared with rover
#pragma once
#include "utils.hpp"

enum class Direction : int { None = -1, Forward = 0, Backward = 1 };

namespace RoverConstants {
constexpr unsigned BufferSize{128};
constexpr int DeadZone{10};
}  // namespace RoverConstants

// Namespace for serial port constants
namespace SerialConstant {
constexpr bool EnabledByDefault{false};
constexpr unsigned long BaudRate{128000};
}  // namespace SerialConstant

// Namespace for JSON constants
namespace JsonConstant {
constexpr char const* Speed{"CSPD"};
constexpr char const* Turning{"CTRN"};
constexpr char const* ArmTurntable{"ATRN"};
constexpr char const* ArmShoulder{"ASHL"};
constexpr char const* ArmForearm{"AFRA"};
constexpr char const* ArmWrist{"AWRS"};
constexpr char const* ArmCramp{"ACRP"};
}  // namespace JsonConstant

namespace RF24Constant {
constexpr unsigned char RadioAddress[6]{"AROVR"};
constexpr unsigned char RoverAddress[6]{"ZROVR"};
constexpr unsigned PayloadSize{32};
constexpr unsigned MessageMaxDelay{5};
constexpr unsigned Timeout{250};
constexpr unsigned Channel{100};
}  // namespace RF24Constant