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
private:
    /* CORE */
    size_t encode_int32(int32_t value, void *data);

    int32_t decode_int32(std::vector<int8_t> &data);

    size_t encode_int16(int16_t value, void *data);

    int16_t decode_int16(std::vector<int8_t> &data);

    size_t encode_int8(int8_t value, void *data);

    int8_t decode_int8(std::vector<int8_t> &data);

    /* ###### */

public:

    std::string decode_string(std::vector<int8_t> &data, size_t len);

    size_t encode_string(const std::string &str, void *data, size_t len);

    size_t encode_game_code(int game_code, void *data);

    int decode_game_code(std::vector<int8_t> &data);


    size_t encode_action_type(ActionType type, void *data);

    ActionType decode_action_type(std::vector<int8_t> &data);

    size_t encode_player_id(int player_id, void *data);

    int decode_player_id(std::vector<int8_t> &data);

    size_t encode_event_type(EventType type, void *data);

    EventType decode_event_type(std::vector<int8_t> &data);

    size_t encode_bool(bool value, void *data);

    bool decode_bool(std::vector<int8_t> &data);

    size_t encode_game_mode(GameMode game_mode, void *data);

    GameMode decode_game_mode(std::vector<int8_t> &data);

    size_t encode_coordinate(int coordinate, void *data);

    int16_t decode_coordinate(std::vector<int8_t> &data);

    int decode_len(std::vector<int8_t> &data);

    size_t encode_len(int players_len, void *data);

    size_t encode_player_state(State state, void *data);

    State decode_player_state(std::vector<int8_t> &data);

    int decode_max_players(std::vector<int8_t> &data);

    size_t encode_max_players(int max_players, void *data);

    size_t encode_actual_players(int actual_players, void *data);

    int decode_actual_players(std::vector<int8_t> &data);

    size_t encode_id(int id, void *data);

    int decode_id(std::vector<int8_t> &data);

    size_t encode_tile_id(int tile_id, void *data);

    int decode_tile_id(std::vector<int8_t> &data);

    size_t encode_background_id(int background_id, void *data);

    int decode_background_id(std::vector<int8_t> &data);

    size_t encode_angle(float value, signed char *string);

    float decode_angle(std::vector<int8_t> &data);

    size_t encode_score(int score, void *data);

    int decode_score(std::vector<int8_t> &data);
};

#endif // TALLER_TP_ENCODER_H
