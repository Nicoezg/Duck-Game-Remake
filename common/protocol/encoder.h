#ifndef TP_2_THREADS_COMMON_ENCODER_H
#define TP_2_THREADS_COMMON_ENCODER_H

#include <cstdint>
#include <string>
#include <vector>

#include "action.h"
class Encoder {
public:
  int8_t encode_action_name(const std::string &action);

  int8_t encode_event_type(const std::string &event_type);


  std::string decode_action_type(const int8_t &event_type);


  std::string decode_action_name(const int8_t &action_code);

};

#endif // TP_2_THREADS_COMMON_ENCODER_H
