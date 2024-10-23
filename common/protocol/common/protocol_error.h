#ifndef TALLER_TP_PROTOCOL_ERROR_H
#define TALLER_TP_PROTOCOL_ERROR_H

#include <exception>
class ProtocolError : public std::exception {
private:
  char message[256];

public:
  explicit ProtocolError(const char *message);

  const char *what() const noexcept override;
};

#endif // TALLER_TP_PROTOCOL_ERROR_H
