#ifndef TALLER_TP_ENCODER_H
#define TALLER_TP_ENCODER_H

#include <cstdint>
#include <string>
#include <vector>

#include "common/actions/connection/create.h"
#include "common/events/base/event_type.h"
#include "common/game_mode.h"
#include "common/events/player_macros.h"

class Encoder {
public:
    /* COMMON */
    size_t encode_game_code(uint32_t game_code, void *data);

    uint32_t decode_game_code(std::vector<int8_t> &data);

    /* ACTIONS */
    size_t encode_action_type(ActionType type, void *data);

    ActionType decode_action_type(std::vector<int8_t> &data);

    /* EVENTS */
    size_t encode_player_id(uint16_t player_id, void *data);

    uint16_t decode_player_id(std::vector<int8_t> &data);

    size_t encode_event_type(EventType type, void *data);

    EventType decode_event_type(std::vector<int8_t> &data);

    size_t encode_connected(bool is_connected, void *data);

    bool decode_connected(std::vector<int8_t> &data);

    size_t encode_game_mode(GameMode game_mode, void *data);

    GameMode decode_game_mode(std::vector<int8_t> &data);

    size_t encode_is_right(bool is_right, void *data);

    bool decode_is_right(std::vector<int8_t> &data);

    size_t encode_coordinate(int16_t coordinate, void *data);

    int16_t decode_coordinate(std::vector<int8_t> &data);

    int decode_len(std::vector<int8_t> &data);

    size_t encode_len(uint8_t players_len, void *data);

    size_t encode_player_state(State state, void *data);

    State decode_player_state(std::vector<int8_t> &data);

    int decode_max_players(std::vector<int8_t> &data);

    size_t encode_max_players(uint8_t max_players, void *data);

    size_t encode_actual_players(uint8_t actual_players, void *data);

    int decode_actual_players(std::vector<int8_t> &data);


    size_t encode_bool(bool is_connected, void *data);

    bool decode_bool(std::vector<int8_t> &data);

    size_t encode_id(uint8_t id, void *data);

    uint8_t decode_id(std::vector<int8_t> &data);

    size_t encode_tile_id(uint8_t tile_id, void *data);

    uint8_t decode_tile_id(std::vector<int8_t> &data);

    size_t encode_background_id(uint8_t background_id, void *data);

    uint8_t decode_background_id(std::vector<int8_t> &data);

    size_t encode_angle(float value, signed char *string);

    float decode_angle(std::vector<int8_t> &data);

    size_t encode_score(int16_t score, void *data);

    int decode_score(std::vector<int8_t> &data);

    std::string decode_string(std::vector<int8_t> &data, size_t len);

    size_t encode_string(const std::string &str, void *data, size_t len);
};

#endif // TALLER_TP_ENCODER_H
