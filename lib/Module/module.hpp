#pragma once

/*
  Abstract class representing an Arduino module with common basic functionality
*/

class ArduinoModule {
 public:
  // Change it if you'll use the modules with different ADC resolution
  constexpr static int ADC_RESOLUTION_VALUE{1024};
  constexpr static int PWM_MAX_VALUE{255};

  virtual bool initialize() = 0;

  bool initialized() const { return m_initialized; }
  bool pins_set() const { return m_pins_set; }

 protected:
  bool m_initialized{false};
  bool m_pins_set{false};
};