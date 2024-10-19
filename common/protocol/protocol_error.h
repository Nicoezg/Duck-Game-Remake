//
// Created by fran on 02/05/24.
//

#ifndef TP_2_THREADS_COMMON_PROTOCOL_ERROR_H
#define TP_2_THREADS_COMMON_PROTOCOL_ERROR_H

#include <exception>
class ProtocolError : public std::exception {
private:
  char message[256];

public:
  explicit ProtocolError(const char *message);

  const char *what() const noexcept override;
};

#endif // TP_2_THREADS_COMMON_PROTOCOL_ERROR_H
