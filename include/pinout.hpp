#pragma once

/*
  Pinout constants for the rover
*/

namespace Pin {
namespace Chassis {
namespace Direction {
constexpr unsigned Right{41};
constexpr unsigned Left{40};
}  // namespace Direction

namespace PWM {
constexpr unsigned Left{11};
constexpr unsigned Right{12};
}  // namespace PWM

}  // namespace Chassis

namespace Arm {
namespace Direction {
constexpr unsigned TurntableRight{29};
constexpr unsigned TurntableLeft{28};
constexpr unsigned ShoulderUp{30};
constexpr unsigned ShoulderDown{31};
constexpr unsigned ForearmUp{32};
constexpr unsigned ForearmDown{33};
constexpr unsigned WristUp{34};
constexpr unsigned WristDown{35};
constexpr unsigned CrampTighten{37};
constexpr unsigned CrampRelease{36};
}  // namespace Direction

namespace PWM {
constexpr unsigned Turntable{3};
constexpr unsigned Shoulder{4};
constexpr unsigned Forearm{5};
constexpr unsigned Wrist{6};
constexpr unsigned Cramp{7};
}  // namespace PWM

}  // namespace Arm

constexpr unsigned RF24Enable{9};
constexpr unsigned RF24Select{10};
}  // namespace Pin