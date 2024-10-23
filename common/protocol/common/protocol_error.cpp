#include "protocol_error.h"

#include <cstring>

ProtocolError::ProtocolError(const char *msg_error) {
  strncpy(message, msg_error, sizeof(message));
  message[sizeof(message) - 1] = '\0';
}

const char *ProtocolError::what() const noexcept { return message; }
