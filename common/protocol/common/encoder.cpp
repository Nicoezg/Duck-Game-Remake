#include "encoder.h"
#include <stdexcept>
#include <cstring>
#include <netinet/in.h>
#include <cmath>

/* ####### CORE ####### */

size_t Encoder::encode_int32(int32_t value, void *data) {
  int32_t network_value = htonl(value);
  const auto *value_bytes = reinterpret_cast<int8_t *>(&network_value);
  std::memcpy(data, value_bytes, sizeof(int32_t));
  return sizeof(int32_t);
}

int32_t Encoder::decode_int32(std::vector<int8_t> &data) {
    if (data.size() < sizeof(int32_t)) {
        throw std::runtime_error("No hay suficientes bytes para decodificar el entero de 32 bits.");
    }
    int32_t value;
    std::memcpy(&value, data.data(), sizeof(int32_t));
    data.erase(data.begin(), data.begin() + sizeof(int32_t));
    return ntohl(value);
}

size_t Encoder::encode_int16(int16_t value, void *data) {
  int16_t network_value = htons(value);
  const auto *value_bytes = reinterpret_cast<int8_t *>(&network_value);
  std::memcpy(data, value_bytes, sizeof(int16_t));
  return sizeof(int16_t);
}

int16_t Encoder::decode_int16(std::vector<int8_t> &data) {
    if (data.size() < sizeof(int16_t)) {
        throw std::runtime_error("No hay suficientes bytes para decodificar el entero de 16 bits.");
    }
    int16_t value;
    std::memcpy(&value, data.data(), sizeof(int16_t));
    value = ntohs(value);
    data.erase(data.begin(), data.begin() + sizeof(int16_t));
    return value;
}

size_t Encoder::encode_int8(int8_t value, void *data) {
  const auto *value_bytes = reinterpret_cast<int8_t *>(&value);
  std::memcpy(data, value_bytes, sizeof(int8_t));
  return sizeof(int8_t);
}

int8_t Encoder::decode_int8(std::vector<int8_t> &data) {
  if (data.size() < sizeof(int8_t)) {
    throw std::runtime_error("No hay suficientes bytes para decodificar el entero de 8 bits.");
  }
  int8_t value;
  std::memcpy(&value, data.data(), sizeof(int8_t));
  data.erase(data.begin(), data.begin() + sizeof(int8_t));
  return value;
}

std::string Encoder::decode_string(std::vector<int8_t> &data, size_t len) {
    if (data.size() < len) {
        throw std::runtime_error("No hay suficientes bytes para decodificar el string.");
    }
    std::string str(data.begin(), data.begin() + len);
    data.erase(data.begin(), data.begin() + len);
    return str;
}

size_t Encoder::encode_string(const std::string &str, void *data, size_t len) {
    std::memcpy(data, str.c_str(), len);
    return len;
}

/* ############################### */


size_t Encoder::encode_game_code(int game_code, void *data) {
  return encode_int32(game_code, data);
}

int Encoder::decode_game_code(std::vector<int8_t> &data) {
  return decode_int32(data);
}

size_t Encoder::encode_action_type(ActionType type, void *data) {
  return encode_int8(type, data);
}

ActionType Encoder::decode_action_type(std::vector<int8_t> &data) {
    return ActionType(decode_int8(data));
}

size_t Encoder::encode_event_type(EventType type, void *data) {
    return encode_int8(type, data);
}

EventType Encoder::decode_event_type(std::vector<int8_t> &data) {
  return EventType(decode_int8(data));
}

size_t Encoder::encode_player_id(int player_id, void *data) {
  return encode_int16(player_id, data);
}

int Encoder::decode_player_id(std::vector<int8_t> &data) {
  return decode_int16(data);
}

size_t Encoder::encode_bool(bool value, void *data) {
  return encode_int8(value, data);
}

bool Encoder::decode_bool(std::vector<int8_t> &data) {
  return decode_int8(data);
}

size_t Encoder::encode_game_mode(GameMode game_mode, void *data) {
  return encode_int8(game_mode, data);
}

GameMode Encoder::decode_game_mode(std::vector<int8_t> &data) {
  return GameMode(decode_int8(data));
}

State Encoder::decode_player_state(std::vector<int8_t> &data) {
  return State(decode_int8(data));
}

size_t Encoder::encode_player_state(State state, void *data) {
  return encode_int8(state, data);
}

size_t Encoder::encode_coordinate(int coordinate, void *data) {
    return encode_int16(coordinate, data);
}

int16_t Encoder::decode_coordinate(std::vector<int8_t> &data) {
    return decode_int16(data);
}

int Encoder::decode_len(std::vector<int8_t> &data) {
  return decode_int8(data);
}

size_t Encoder::encode_len(int players_len, void *data) {
  return encode_int8(players_len, data);
}

int Encoder::decode_max_players(std::vector<int8_t> &data) {
  return decode_int8(data);
}

size_t Encoder::encode_max_players(int max_players, void *data) {
  return encode_int8(max_players, data);
}

size_t Encoder::encode_actual_players(int actual_players, void *data) {
    return encode_int8(actual_players, data);
}

int Encoder::decode_actual_players(std::vector<int8_t> &data) {
    return decode_int8(data);
}

size_t Encoder::encode_id(int id, void *data) {
    return encode_int8(id, data);
}

int Encoder::decode_id(std::vector<int8_t> &data) {
    return decode_int8(data);
}

size_t Encoder::encode_tile_id(int tile_id, void *data) {
    return encode_int8(tile_id, data);
}

int Encoder::decode_tile_id(std::vector<int8_t> &data) {
    return decode_int8(data);
}

size_t Encoder::encode_background_id(int background_id, void *data) {
    return encode_int8(background_id, data);
}

int Encoder::decode_background_id(std::vector<int8_t> &data) {
    return decode_int8(data);
}

size_t Encoder::encode_angle(float value, signed char *string) {
    int16_t angle = value * 100;
    return encode_int16(angle, string);
}

float Encoder::decode_angle(std::vector<int8_t> &data) {
    int16_t angle = decode_int16(data);
    return angle / 100.0;
}

size_t Encoder::encode_score(int score, void *data) {
    return encode_int16(score, data);
}

int Encoder::decode_score(std::vector<int8_t> &data) {
    return decode_int16(data);
}
