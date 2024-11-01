#include "protocol.h"

#include "protocol_error.h"

Protocol::Protocol(Socket *socket) : socket(socket), is_closed(false) {}

void Protocol::read(void *data, size_t size) {
  if (is_closed) {
    throw ProtocolError("protocol was closed. Cannot read data.");
  }
  bool was_closed = false;
  socket->recvall(data, size, &was_closed);
  if (was_closed) {
    is_closed = true;
    throw ProtocolError("protocol was closed when reading data");
  }
}

void Protocol::send(void *data, size_t size) {
  if (is_closed) {
    throw ProtocolError("protocol is closed. Cannot send data.");
  }
  bool was_closed = false;
  socket->sendall(data, size, &was_closed);
  if (was_closed) {
    is_closed = true;
    throw ProtocolError("protocol was closed when sending data");
  }
}

bool Protocol::is_open() { return !is_closed; }

void Protocol::close() { is_closed = true; }
