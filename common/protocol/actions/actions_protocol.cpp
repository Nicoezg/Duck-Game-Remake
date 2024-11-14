//
// Created by fran on 22/10/24.
//

#include "actions_protocol.h"

#include "common/actions/connection/join.h"
#include "common/actions/player/move.h"
#include "common/actions/player/jump_flap.h"
#include "common/actions/player/still.h"
#include "common/actions/player/play_dead.h"
#include "common/actions/player/shoot.h"
#include "common/actions/player/aim_upwards.h"
#include "common/actions/player/pick_drop.h"
#include "common/actions/connection/refresh_games.h"
#include <stdexcept>
#include <iostream>

#define ACTION_TYPE_SIZE sizeof(int8_t)
#define GAME_CODE_SIZE sizeof(uint32_t)
#define GAME_MODE_SIZE sizeof(int8_t)
#define PLAYER_ID_SIZE sizeof(uint16_t)
#define MAX_PLAYER_SIZE sizeof(uint8_t)
#define IS_RIGHT_SIZE sizeof(uint8_t)

#define READ_JOIN_SIZE (GAME_CODE_SIZE + GAME_MODE_SIZE)
#define READ_CREATE_SIZE (GAME_MODE_SIZE + MAX_PLAYER_SIZE)
#define READ_MOVE_SIZE (PLAYER_ID_SIZE + IS_RIGHT_SIZE)
#define READ_JUMP_SIZE (PLAYER_ID_SIZE + IS_RIGHT_SIZE)
#define READ_STILL_SIZE (PLAYER_ID_SIZE + IS_RIGHT_SIZE)
#define READ_PLAY_DEAD_SIZE (PLAYER_ID_SIZE + IS_RIGHT_SIZE)
#define READ_SHOOT_SIZE (PLAYER_ID_SIZE + IS_RIGHT_SIZE)
#define READ_AIMING_UPWARDS_SIZE (PLAYER_ID_SIZE + IS_RIGHT_SIZE)
#define READ_PICK_DROP_SIZE (PLAYER_ID_SIZE + IS_RIGHT_SIZE)

#define SEND_JOIN_SIZE (ACTION_TYPE_SIZE + READ_JOIN_SIZE)
#define SEND_CREATE_SIZE (ACTION_TYPE_SIZE + READ_CREATE_SIZE)
#define SEND_MOVE_SIZE (ACTION_TYPE_SIZE + READ_MOVE_SIZE)
#define SEND_JUMP_SIZE (ACTION_TYPE_SIZE + READ_JUMP_SIZE)
#define SEND_STILL_SIZE (ACTION_TYPE_SIZE + READ_STILL_SIZE)
#define SEND_PLAY_DEAD_SIZE (ACTION_TYPE_SIZE + READ_PLAY_DEAD_SIZE)
#define SEND_SHOOT_SIZE (ACTION_TYPE_SIZE + READ_SHOOT_SIZE)
#define SEND_AIMING_UPWARDS_SIZE (ACTION_TYPE_SIZE + READ_AIMING_UPWARDS_SIZE)
#define SEND_PICK_DROP_SIZE (ACTION_TYPE_SIZE + READ_PICK_DROP_SIZE)

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

        case START:
            return std::make_shared<Action>(START);
        case JUMP_FLAP:
            return read_jump_flap_action();
        case STILL:
            return read_still_action();
        case PLAY_DEAD:
            return read_play_dead_action();
        case SHOOT:
            return read_shoot_action();
        case AIM_UPWARDS:
            return read_aiming_upwards_action();
        case PICK_DROP:
            return read_pick_drop_action();

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

        case START:
            return send_start(action);
        case JUMP_FLAP:
            return send_jump_flap_action(action);
        case STILL:
            return send_still_action(action);
        case PLAY_DEAD:
            return send_play_dead_action(action);
        case SHOOT:
            std::cout << "entro a shoot" << std::endl;
            return send_shoot_action(action);
        case AIM_UPWARDS:
            return send_aiming_upwards_action(action);
        case PICK_DROP:
            std::cout << "entro a pick drop" << std::endl;
            return send_pick_drop_action(action);
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

void ActionsProtocol::send_jump_flap_action(const std::shared_ptr<Action> &action) {
    std::vector<int8_t> data(SEND_JUMP_SIZE);
    size_t offset = 0;
    offset += encoder.encode_action_type(action->get_type(), &data[offset]);
    offset += encoder.encode_player_id(action->get_player_id(), &data[offset]);
    encoder.encode_is_right(action->is_jumping_flapping(), &data[offset]);
    send(data.data(), data.size());
}

void ActionsProtocol::send_still_action(const std::shared_ptr<Action> &action) {
    std::vector<int8_t> data(SEND_STILL_SIZE);
    size_t offset = 0;
    offset += encoder.encode_action_type(action->get_type(), &data[offset]);
    offset += encoder.encode_player_id(action->get_player_id(), &data[offset]);
    encoder.encode_is_right(action->is_still(), &data[offset]);
    send(data.data(), data.size());
}

void ActionsProtocol::send_play_dead_action(const std::shared_ptr<Action> &action) {
    std::vector<int8_t> data(SEND_PLAY_DEAD_SIZE);
    size_t offset = 0;
    offset += encoder.encode_action_type(action->get_type(), &data[offset]);
    offset += encoder.encode_player_id(action->get_player_id(), &data[offset]);
    encoder.encode_is_right(action->is_playing_dead(), &data[offset]);
    send(data.data(), data.size());
}

void ActionsProtocol::send_shoot_action(const std::shared_ptr<Action> &action) {
    std::vector<int8_t> data(SEND_SHOOT_SIZE);
    size_t offset = 0;
    offset += encoder.encode_action_type(action->get_type(), &data[offset]);
    offset += encoder.encode_player_id(action->get_player_id(), &data[offset]);
    std::cout << "llego aca" << std::endl;
    encoder.encode_is_right(action->is_shooting(), &data[offset]);
    std::cout << "lo paso" << std::endl;
    send(data.data(), data.size());
}

void ActionsProtocol::send_aiming_upwards_action(const std::shared_ptr<Action> &action) {
    std::vector<int8_t> data(SEND_AIMING_UPWARDS_SIZE);
    size_t offset = 0;
    offset += encoder.encode_action_type(action->get_type(), &data[offset]);
    offset += encoder.encode_player_id(action->get_player_id(), &data[offset]);
    encoder.encode_is_right(action->is_aiming_upwards(), &data[offset]);
    send(data.data(), data.size());
}

void ActionsProtocol::send_pick_drop_action(const std::shared_ptr<Action> &action) {
    std::vector<int8_t> data(SEND_PICK_DROP_SIZE);
    size_t offset = 0;
    offset += encoder.encode_action_type(action->get_type(), &data[offset]);
    offset += encoder.encode_player_id(action->get_player_id(), &data[offset]);
    encoder.encode_is_right(action->is_picking_dropping(), &data[offset]);
    send(data.data(), data.size());
}

std::shared_ptr<Action> ActionsProtocol::read_move_action() {
    std::vector<int8_t> data(READ_MOVE_SIZE);
    read(data.data(), data.size());
    int player_id = encoder.decode_player_id(data);
    bool is_right = encoder.decode_is_right(data);
    return std::make_shared<Move>(player_id, is_right);
}

void ActionsProtocol::send_start(const std::shared_ptr<Action> &action) {
    std::vector<int8_t> data(ACTION_TYPE_SIZE);
    size_t offset = 0;
    offset += encoder.encode_action_type(action->get_type(), &data[offset]);
    send(data.data(), data.size());
}

std::shared_ptr<Action> ActionsProtocol::read_jump_flap_action() {
    std::vector<int8_t> data(READ_JUMP_SIZE);
    read(data.data(), data.size());
    int player_id = encoder.decode_player_id(data);
    bool is_right = encoder.decode_is_right(data);
    return std::make_shared<JumpFlap>(player_id, is_right);
}

std::shared_ptr<Action> ActionsProtocol::read_still_action() {
    std::vector<int8_t> data(READ_STILL_SIZE);
    read(data.data(), data.size());
    int player_id = encoder.decode_player_id(data);
    bool is_right = encoder.decode_is_right(data);
    return std::make_shared<Still>(player_id, is_right);
}

std::shared_ptr<Action> ActionsProtocol::read_play_dead_action() {
    std::vector<int8_t> data(READ_PLAY_DEAD_SIZE);
    read(data.data(), data.size());
    int player_id = encoder.decode_player_id(data);
    bool is_right = encoder.decode_is_right(data);
    return std::make_shared<PlayDead>(player_id, is_right);
}

std::shared_ptr<Action> ActionsProtocol::read_shoot_action() {
    std::vector<int8_t> data(READ_SHOOT_SIZE);
    read(data.data(), data.size());
    int player_id = encoder.decode_player_id(data);
    bool is_right = encoder.decode_is_right(data);
    return std::make_shared<Shoot>(player_id, is_right);
}

std::shared_ptr<Action> ActionsProtocol::read_aiming_upwards_action() {
    std::vector<int8_t> data(READ_AIMING_UPWARDS_SIZE);
    read(data.data(), data.size());
    int player_id = encoder.decode_player_id(data);
    bool is_right = encoder.decode_is_right(data);
    return std::make_shared<AimUpwards>(player_id, is_right);
}

std::shared_ptr<Action> ActionsProtocol::read_pick_drop_action() {
    std::vector<int8_t> data(READ_PICK_DROP_SIZE);
    read(data.data(), data.size());
    int player_id = encoder.decode_player_id(data);
    bool is_right = encoder.decode_is_right(data);
    return std::make_shared<PickDrop>(player_id, is_right);
}