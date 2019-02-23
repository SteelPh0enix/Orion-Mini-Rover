#include "receiver.hpp"
#include <printf.h>
#include "../../include/constants.hpp"
#include "../../include/utils.hpp"

void Receiver::initialize() {
  m_radio.begin();
  m_radio.setAutoAck(1);
  m_radio.setPayloadSize(RF24Constant::PayloadSize);
  m_radio.setPALevel(RF24_PA_MAX);
  m_radio.setDataRate(RF24_250KBPS);
  m_radio.setCRCLength(RF24_CRC_16);
  m_radio.openWritingPipe(RF24Constant::RoverAddress);
  m_radio.openReadingPipe(1, RF24Constant::RadioAddress);
  m_radio.startListening();
  printf_begin();

  m_initialized = true;
}

bool Receiver::initialized() const { return m_initialized; }

void Receiver::read_data(char* data) {
  if (!initialized()) return;

  unsigned buffer_position{0};
  char buffer[RF24Constant::PayloadSize + 1]{};

  // While whole message isn't received...
  while (Utility::last_char(buffer) != '}') {
    if (m_radio.available()) {
      // Receive next packet
      m_radio.read(buffer, RF24Constant::PayloadSize);
      // Check if it's first packet
      if (Utility::first_char(buffer) == '{') {
        strcpy(data, buffer);
        buffer_position = RF24Constant::PayloadSize;
      } else {
        // If it's not, then it's probably next packet
        strcpy(data + buffer_position, buffer);
        buffer_position += RF24Constant::PayloadSize;
      }
    } else {
      // Or wait for it
      delay(RF24Constant::MessageMaxDelay);
    }
  }
}

void Receiver::print_debug_data() { m_radio.printDetails(); }