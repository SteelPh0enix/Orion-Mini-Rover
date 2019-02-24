#pragma once
#include <RF24.h>
#include "../../include/pinout.hpp"

/*
  Class used to communicate with rover
*/

class Receiver {
 public:
  void initialize();
  bool initialized() const;

  void read_data(char* data);

  void print_debug_data();

 private:
  bool m_initialized{false};
  RF24 m_radio{Pin::RF24Enable, Pin::RF24Select};
};