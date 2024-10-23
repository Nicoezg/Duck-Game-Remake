#ifndef TALLER_TP_ENCODER_H
#define TALLER_TP_ENCODER_H

#include <cstdint>
#include <string>
#include <vector>

#include "common/actions/create.h"
#include "common/events/event_type.h"

class Encoder {
public:

    /* COMMON */
    size_t encode_game_code(uint32_t game_code, void* data);

    uint32_t decode_game_code(std::vector<int8_t> &data);

    /* ACTIONS */
    size_t encode_action_type(ActionType type, void* data);

    ActionType decode_action_type(std::vector<int8_t> &data);

    /* EVENTS */
    size_t encode_player_id(uint16_t player_id, void* data);

    uint16_t decode_player_id(std::vector<int8_t> &data);

    size_t encode_event_type(EventType type, void* data);

    EventType decode_event_type(std::vector<int8_t> &data);

    size_t encode_connected(bool is_connected, void* data);

    bool decode_connected(std::vector<int8_t> &data);
};

#endif // TALLER_TP_ENCODER_H
