#include "common/protocol/encoder.h"

#include <stdexcept>

#include <cstring>
#include <netinet/in.h>

#include "common/protocol/action.h"
#include "common/protocol/action_macros.h"

int8_t Encoder::encode_action_name(const std::string &action) {
  if (action == ACTION_ATTACK) {
    return ATTACK;
  } else if (action == ACTION_BROADCAST) {
      return BROADCAST;
  }
  throw std::runtime_error("encoder try to encode unknown action");
}


std::string Encoder::decode_action_name(const int8_t &action_code) {
  switch (action_code) {
  case ATTACK:
    return ACTION_ATTACK;
  case BROADCAST:
    return ACTION_BROADCAST;
  default:
    throw std::runtime_error("encoder try to decode unknown action");
  }
}
