#include "encoder.h"

#include <stdexcept>

#include <cstring>
#include <netinet/in.h>

#include "common/actions/create.h"
#include "common/actions/action_macros.h"

/* Comunes */
size_t Encoder::encode_game_code(uint32_t game_code, void* data) {

    uint32_t network_game_code = htonl(game_code);
    auto *game_code_bytes = reinterpret_cast<int8_t *>(&network_game_code);
    std::memcpy(data, game_code_bytes, sizeof(uint32_t));
    return sizeof(uint32_t);
}

uint32_t Encoder::decode_game_code(std::vector<int8_t> &data) {
    if (data.size() < sizeof(uint32_t)) {
        throw std::runtime_error("No hay suficientes bytes para decodificar el codigo de juego.");
    }
    uint32_t game_code;
    std::memcpy(&game_code, data.data(), sizeof(uint32_t));
    game_code = ntohl(game_code);
    data.erase(data.begin(), data.begin() + sizeof(uint32_t));
    return game_code;
}


/* Acciones */
size_t Encoder::encode_action_type(ActionType type, void* data) {
    auto *action_type_bytes = reinterpret_cast<int8_t *>(&type);
    std::memcpy(data, action_type_bytes, sizeof(int8_t));
    return sizeof(int8_t);
}

ActionType Encoder::decode_action_type(std::vector<int8_t> &data) {
    if (data.size() < sizeof(int8_t)) {
        throw std::runtime_error("No hay suficientes bytes para decodificar el tipo de accion.");
    }
    auto type = static_cast<ActionType>(data[0]);
    data.erase(data.begin(), data.begin() + sizeof(int8_t));
    return type;
}


/* Eventos */
size_t Encoder::encode_event_type(EventType type, void* data) {
    auto *event_type_bytes = reinterpret_cast<int8_t *>(&type);
    std::memcpy(data, event_type_bytes, sizeof(int8_t));
    return sizeof(int8_t);
}

EventType Encoder::decode_event_type(std::vector<int8_t> &data) {
    if (data.size() < sizeof(int8_t)) {
        throw std::runtime_error("No hay suficientes bytes para decodificar el tipo de accion.");
    }
    auto type = static_cast<EventType>(data[0]);
    data.erase(data.begin(), data.begin() + sizeof(int8_t));
    return type;
}

size_t Encoder::encode_player_id(uint16_t player_id, void* data) {
    uint16_t network_player_id = htons(player_id);
    auto *player_id_bytes = reinterpret_cast<int8_t *>(&network_player_id);
    std::memcpy(data, player_id_bytes, sizeof(uint16_t));
    return sizeof(uint16_t);
}

uint16_t Encoder::decode_player_id(std::vector<int8_t> &data) {
    if (data.size() < sizeof(uint16_t)) {
        throw std::runtime_error("No hay suficientes bytes para decodificar el id de jugador.");
    }
    uint16_t player_id;
    std::memcpy(&player_id, data.data(), sizeof(uint16_t));
    player_id = ntohs(player_id);
    data.erase(data.begin(), data.begin() + sizeof(uint16_t));
    return player_id;
}

size_t Encoder::encode_connected(bool is_connected, void* data) {
    auto connected = static_cast<int8_t>(is_connected);
    std::memcpy(data, &connected, sizeof(int8_t));
    return sizeof(int8_t);
}

bool Encoder::decode_connected(std::vector<int8_t> &data) {
    if (data.size() < sizeof(int8_t)) {
        throw std::runtime_error("No hay suficientes bytes para decodificar la conexion.");
    }
    auto connected = static_cast<bool>(data[0]);
    data.erase(data.begin(), data.begin() + sizeof(int8_t));
    return connected;
}

size_t Encoder::encode_game_mode(GameMode game_mode, void *data) {
    auto *game_mode_bytes = reinterpret_cast<int8_t *>(&game_mode);
    std::memcpy(data, game_mode_bytes, sizeof(int8_t));
    return sizeof(int8_t);
}

GameMode Encoder::decode_game_mode(std::vector<int8_t> &data) {
    if (data.size() < sizeof(int8_t)) {
        throw std::runtime_error("No hay suficientes bytes para decodificar el modo de juego.");
    }
    auto game_mode = static_cast<GameMode>(data[0]);
    data.erase(data.begin(), data.begin() + sizeof(int8_t));
    return game_mode;
}
