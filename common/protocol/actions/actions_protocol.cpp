//
// Created by fran on 22/10/24.
//

#include "actions_protocol.h"

#include "common/actions/connection/join.h"
#include "common/actions/player/move.h"
#include "common/actions/connection/refresh_games.h"
#include <stdexcept>

#define ACTION_TYPE_SIZE sizeof(int8_t)
#define GAME_CODE_SIZE sizeof(uint32_t)
#define GAME_MODE_SIZE sizeof(int8_t)
#define PLAYER_ID_SIZE sizeof(uint16_t)
#define MAX_PLAYER_SIZE sizeof(uint8_t)
#define IS_RIGHT_SIZE sizeof(uint8_t)

#define READ_JOIN_SIZE (GAME_CODE_SIZE + GAME_MODE_SIZE)
#define READ_CREATE_SIZE (GAME_MODE_SIZE + MAX_PLAYER_SIZE)
#define READ_MOVE_SIZE (PLAYER_ID_SIZE + IS_RIGHT_SIZE)

#define SEND_JOIN_SIZE (ACTION_TYPE_SIZE + READ_JOIN_SIZE)
#define SEND_CREATE_SIZE (ACTION_TYPE_SIZE + READ_CREATE_SIZE)
#define SEND_MOVE_SIZE (ACTION_TYPE_SIZE + READ_MOVE_SIZE)

ActionsProtocol::ActionsProtocol(Socket *socket, Encoder encoder)
        : Protocol(socket), encoder(encoder) {}

std::shared_ptr<Action> ActionsProtocol::read_create_action() {
    std::vector<int8_t> data(READ_CREATE_SIZE);
    read(data.data(), data.size());
    GameMode game_mode = encoder.decode_game_mode(data);
    int max_players = encoder.decode_max_players(data);
    return std::make_shared<Create>(game_mode, max_players);
}

std::shared_ptr<Action> ActionsProtocol::read_join_action() {
    std::vector<int8_t> data(READ_JOIN_SIZE);
    read(data.data(), data.size());
    int game_code = encoder.decode_game_code(data);
    GameMode game_mode = encoder.decode_game_mode(data);
    return std::make_shared<Join>(game_code, game_mode);
}

std::shared_ptr<Action> ActionsProtocol::read_element() {
    switch (read_action_type()) {
        case CREATE_REQUEST:
            return read_create_action();
        case JOIN_REQUEST:
            return read_join_action();
        case MOVE:
            return read_move_action();

        case REFRESH_REQUEST:
            return std::make_shared<RefreshGames>();
        default:
            throw std::runtime_error(
                    "ActionsProtocol try to action_read invalid action.");
    }
}

ActionType ActionsProtocol::read_action_type() {
    std::vector<int8_t> data(ACTION_TYPE_SIZE);
    read(data.data(), data.size());
    return encoder.decode_action_type(data);
}

void ActionsProtocol::send_element(const std::shared_ptr<Action> &action) {
    ActionType type = action->get_type();

    switch (type) {
        case CREATE_REQUEST:
            return send_create_action(action);
        case JOIN_REQUEST:
            return send_join_action(action);
        case MOVE:
            return send_move_action(action);

        case REFRESH_REQUEST:
            return send_refresh_action(action);
        default:
            throw std::runtime_error("ActionsProtocol try to send unknown action");
    }
}

void ActionsProtocol::send_refresh_action(const std::shared_ptr<Action> &action) {
    std::vector<int8_t> data(ACTION_TYPE_SIZE);
    size_t offset = 0;
    offset += encoder.encode_action_type(action->get_type(), &data[offset]);
    send(data.data(), data.size());
}

void ActionsProtocol::send_create_action(
        const std::shared_ptr<Action> &action) {
    std::vector<int8_t> data(SEND_CREATE_SIZE);
    size_t offset = 0;
    offset += encoder.encode_action_type(action->get_type(), &data[offset]);
    offset += encoder.encode_game_mode(action->get_game_mode(), &data[offset]);
    offset += encoder.encode_max_players(action->get_max_players(), &data[offset]);
    send(data.data(), SEND_CREATE_SIZE);
}

void ActionsProtocol::send_join_action(const std::shared_ptr<Action> &action) {
    std::vector<int8_t> data(SEND_JOIN_SIZE);
    size_t offset = 0;
    offset += encoder.encode_action_type(action->get_type(), &data[offset]);
    offset += encoder.encode_game_code(action->get_game_code(), &data[offset]);
    offset += encoder.encode_game_mode(action->get_game_mode(), &data[offset]);
    send(data.data(), data.size());
}

void ActionsProtocol::send_move_action(const std::shared_ptr<Action> &action) {
    std::vector<int8_t> data(SEND_MOVE_SIZE);
    size_t offset = 0;
    offset += encoder.encode_action_type(action->get_type(), &data[offset]);
    offset += encoder.encode_player_id(action->get_player_id(), &data[offset]);
    encoder.encode_is_right(action->is_right(), &data[offset]);
    send(data.data(), data.size());
}

std::shared_ptr<Action> ActionsProtocol::read_move_action() {
    std::vector<int8_t> data(READ_MOVE_SIZE);
    read(data.data(), data.size());
    int player_id = encoder.decode_player_id(data);
    bool is_right = encoder.decode_is_right(data);
    return std::make_shared<Move>(player_id, is_right);
}
