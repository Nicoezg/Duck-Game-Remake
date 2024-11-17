#include "encoder.h"
#include "common/events/player_macros.h"

#include <stdexcept>

#include <cstring>
#include <netinet/in.h>

/* Comunes */
size_t Encoder::encode_game_code(uint32_t game_code, void *data) {

  uint32_t network_game_code = htonl(game_code);
  const auto *game_code_bytes = reinterpret_cast<int8_t *>(&network_game_code);
  std::memcpy(data, game_code_bytes, sizeof(uint32_t));
  return sizeof(uint32_t);
}

uint32_t Encoder::decode_game_code(std::vector<int8_t> &data) {
  if (data.size() < sizeof(uint32_t)) {
    throw std::runtime_error(
        "No hay suficientes bytes para decodificar el codigo de juego.");
  }
  uint32_t game_code;
  std::memcpy(&game_code, data.data(), sizeof(uint32_t));
  game_code = ntohl(game_code);
  data.erase(data.begin(), data.begin() + sizeof(uint32_t));
  return game_code;
}

/* Acciones */
size_t Encoder::encode_action_type(ActionType type, void *data) {
  const auto *action_type_bytes = reinterpret_cast<int8_t *>(&type);
  std::memcpy(data, action_type_bytes, sizeof(int8_t));
  return sizeof(int8_t);
}

ActionType Encoder::decode_action_type(std::vector<int8_t> &data) {
  if (data.size() < sizeof(int8_t)) {
    throw std::runtime_error(
        "No hay suficientes bytes para decodificar el tipo de accion.");
  }
  auto type = static_cast<ActionType>(data[0]);
  data.erase(data.begin(), data.begin() + sizeof(int8_t));
  return type;
}

/* Eventos */
size_t Encoder::encode_event_type(EventType type, void *data) {
  const auto *event_type_bytes = reinterpret_cast<int8_t *>(&type);
  std::memcpy(data, event_type_bytes, sizeof(int8_t));
  return sizeof(int8_t);
}

EventType Encoder::decode_event_type(std::vector<int8_t> &data) {
  if (data.size() < sizeof(int8_t)) {
    throw std::runtime_error(
        "No hay suficientes bytes para decodificar el tipo de accion.");
  }
  auto type = static_cast<EventType>(data[0]);
  data.erase(data.begin(), data.begin() + sizeof(int8_t));
  return type;
}

size_t Encoder::encode_player_id(uint16_t player_id, void *data) {
  uint16_t network_player_id = htons(player_id);
  const auto *player_id_bytes = reinterpret_cast<int8_t *>(&network_player_id);
  std::memcpy(data, player_id_bytes, sizeof(uint16_t));
  return sizeof(uint16_t);
}

uint16_t Encoder::decode_player_id(std::vector<int8_t> &data) {
  if (data.size() < sizeof(uint16_t)) {
    throw std::runtime_error(
        "No hay suficientes bytes para decodificar el id de jugador.");
  }
  uint16_t player_id;
  std::memcpy(&player_id, data.data(), sizeof(uint16_t));
  player_id = ntohs(player_id);
  data.erase(data.begin(), data.begin() + sizeof(uint16_t));
  return player_id;
}

size_t Encoder::encode_connected(bool is_connected, void *data) {
  return encode_bool(is_connected, data);
}

size_t Encoder::encode_bool(bool is_connected, void *data) {
  const auto *value = reinterpret_cast<int8_t *>(&is_connected);
  std::memcpy(data, value, sizeof(int8_t));
  return sizeof(int8_t);
}

bool Encoder::decode_connected(std::vector<int8_t> &data) {
  return decode_bool(data);
}

bool Encoder::decode_bool(std::vector<int8_t> &data) {
    if (data.size() < sizeof(int8_t)) {
        throw std::runtime_error(
                "No hay suficientes bytes para decodificar la conexion.");
    }
    const auto *value = reinterpret_cast<int8_t *>(data[0]);
    data.erase(data.begin(), data.begin() + sizeof(int8_t));
    return value;
}

size_t Encoder::encode_game_mode(GameMode game_mode, void *data) {
  const auto *game_mode_bytes = reinterpret_cast<int8_t *>(&game_mode);
  std::memcpy(data, game_mode_bytes, sizeof(int8_t));
  return sizeof(int8_t);
}

GameMode Encoder::decode_game_mode(std::vector<int8_t> &data) {
  if (data.size() < sizeof(int8_t)) {
    throw std::runtime_error(
        "No hay suficientes bytes para decodificar el modo de juego.");
  }
  auto game_mode = static_cast<GameMode>(data[0]);
  data.erase(data.begin(), data.begin() + sizeof(int8_t));
  return game_mode;
}

size_t Encoder::encode_is_right(bool is_right, void *data) {
  const auto *is_right_bytes = reinterpret_cast<int8_t *>(&is_right);
  std::memcpy(data, is_right_bytes, sizeof(int8_t));
  return sizeof(int8_t);
}

bool Encoder::decode_is_right(std::vector<int8_t> &data) {
  if (data.size() < sizeof(int8_t)) {
    throw std::runtime_error(
        "No hay suficientes bytes para decodificar si es correcto.");
  }
  const auto *is_right = reinterpret_cast<int8_t *>(data[0]);
  data.erase(data.begin(), data.begin() + sizeof(int8_t));
  return is_right;
}

State Encoder::decode_player_state(std::vector<int8_t> &data) {
  if (data.size() < sizeof(int8_t)) {
    throw std::runtime_error(
        "No hay suficientes bytes para decodificar el estado del jugador.");
  }
  auto state = static_cast<State>(data[0]);
  data.erase(data.begin(), data.begin() + sizeof(int8_t));
  return state;
}

size_t Encoder::encode_player_state(State state, void *data) {
  const auto *state_bytes = reinterpret_cast<int8_t *>(&state);
  std::memcpy(data, state_bytes, sizeof(int8_t));
  return sizeof(int8_t);
}

/* Posiciones */

size_t Encoder::encode_coordinate(int16_t coordinate, void *data) {
  int16_t network_position = htons(coordinate);
  const auto *position_x_bytes = reinterpret_cast<int8_t *>(&network_position);
  std::memcpy(data, position_x_bytes, sizeof(int16_t));
  return sizeof(int16_t);
}

int16_t Encoder::decode_coordinate(std::vector<int8_t> &data) {
  if (data.size() < sizeof(int16_t)) {
    throw std::runtime_error(
        "No hay suficientes bytes para decodificar la posicion.");
  }
  int16_t coordinate;
  std::memcpy(&coordinate, data.data(), sizeof(int16_t));
  coordinate = ntohs(coordinate);
  data.erase(data.begin(), data.begin() + sizeof(int16_t));
  return coordinate;
}

int Encoder::decode_len(std::vector<int8_t> &data) {
  if (data.size() < sizeof(uint8_t)) {
    throw std::runtime_error(
        "No hay suficientes bytes para decodificar la cantidad de jugadores.");
  }
  uint8_t players_len;
  std::memcpy(&players_len, data.data(), sizeof(uint8_t));
  data.erase(data.begin(), data.begin() + sizeof(uint8_t));
  return players_len;
}

size_t Encoder::encode_len(uint8_t players_len, void *data) {
  const auto *players_len_bytes = reinterpret_cast<int8_t *>(&players_len);
  std::memcpy(data, players_len_bytes, sizeof(uint8_t));
  return sizeof(uint8_t);
}

int Encoder::decode_max_players(std::vector<int8_t> &data) {
  if (data.size() < sizeof(uint8_t)) {
    throw std::runtime_error(
        "No hay suficientes bytes para decodificar la cantidad maxima de jugadores.");
  }
  uint8_t max_players;
  std::memcpy(&max_players, data.data(), sizeof(uint8_t));
  data.erase(data.begin(), data.begin() + sizeof(uint8_t));
  return max_players;
}

size_t Encoder::encode_max_players(uint8_t max_players, void *data) {
  const auto *max_players_bytes = reinterpret_cast<int8_t *>(&max_players);
  std::memcpy(data, max_players_bytes, sizeof(uint8_t));
  return sizeof(uint8_t);
}

size_t Encoder::encode_actual_players(uint8_t actual_players, void *data) {
  const auto *actual_players_bytes = reinterpret_cast<int8_t *>(&actual_players);
  std::memcpy(data, actual_players_bytes, sizeof(uint8_t));
  return sizeof(uint8_t);
}

int Encoder::decode_actual_players(std::vector<int8_t> &data) {
  if (data.size() < sizeof(uint8_t)) {
    throw std::runtime_error(
        "No hay suficientes bytes para decodificar la cantidad actual de jugadores.");
  }
  uint8_t actual_players;
  std::memcpy(&actual_players, data.data(), sizeof(uint8_t));
  data.erase(data.begin(), data.begin() + sizeof(uint8_t));
  return actual_players;
}

size_t Encoder::encode_id(uint8_t id, void *data) {
  const auto *id_bytes = reinterpret_cast<int8_t *>(&id);
  std::memcpy(data, id_bytes, sizeof(uint8_t));
  return sizeof(uint8_t);
}

uint8_t Encoder::decode_id(std::vector<int8_t> &data) {
  if (data.size() < sizeof(uint8_t)) {
    throw std::runtime_error(
        "No hay suficientes bytes para decodificar el id.");
  }
  uint8_t id;
  std::memcpy(&id, data.data(), sizeof(uint8_t));
  data.erase(data.begin(), data.begin() + sizeof(uint8_t));
  return id;
}

size_t Encoder::encode_tile_id(uint8_t tile_id, void *data) {
  const auto *tile_id_bytes = reinterpret_cast<int8_t *>(&tile_id);
  std::memcpy(data, tile_id_bytes, sizeof(uint8_t));
  return sizeof(uint8_t);
}

uint8_t Encoder::decode_tile_id(std::vector<int8_t> &data) {
  if (data.size() < sizeof(uint8_t)) {
    throw std::runtime_error(
        "No hay suficientes bytes para decodificar el id del tile.");
  }
  uint8_t tile_id;
  std::memcpy(&tile_id, data.data(), sizeof(uint8_t));
  data.erase(data.begin(), data.begin() + sizeof(uint8_t));
  return tile_id;
}

size_t Encoder::encode_background_id(uint8_t background_id, void *data) {
  const auto *background_id_bytes = reinterpret_cast<int8_t *>(&background_id);
  std::memcpy(data, background_id_bytes, sizeof(uint8_t));
  return sizeof(uint8_t);
}

uint8_t Encoder::decode_background_id(std::vector<int8_t> &data) {
  if (data.size() < sizeof(uint8_t)) {
    throw std::runtime_error(
        "No hay suficientes bytes para decodificar el id del background.");
  }
  uint8_t background_id;
  std::memcpy(&background_id, data.data(), sizeof(uint8_t));
  data.erase(data.begin(), data.begin() + sizeof(uint8_t));
  return background_id;
}