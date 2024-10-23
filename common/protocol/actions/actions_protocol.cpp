//
// Created by fran on 22/10/24.
//

#include "actions_protocol.h"

#include <stdexcept>
#include "common/actions/join.h"

#define ACTION_TYPE_SIZE sizeof(int8_t)
#define READ_JOIN_SIZE sizeof(uint32_t)

#define SEND_JOIN_SIZE (sizeof(uint32_t) + ACTION_TYPE_SIZE)
#define SEND_CREATE_SIZE ACTION_TYPE_SIZE


ActionsProtocol::ActionsProtocol(Socket *socket, Encoder encoder) : Protocol(socket), encoder(encoder){}

std::shared_ptr<Action> ActionsProtocol::read_create_action() {
    return std::make_shared<Create>();
}

std::shared_ptr<Action> ActionsProtocol::read_join_action() {
    std::vector<int8_t> data(READ_JOIN_SIZE);
    read(data.data(), data.size());
    int game_code = encoder.decode_game_code(data);
    return std::make_shared<Join>(game_code);
}

std::shared_ptr<Action> ActionsProtocol::read_element() {
    switch (read_action_type()) {
        case CREATE_REQUEST:
            return read_create_action();
        case JOIN_REQUEST:
            return read_join_action();
    }
    throw std::runtime_error("ActionsProtocol try to action_read invalid action.");
}

ActionType ActionsProtocol::read_action_type() {
    std::vector<int8_t> data(ACTION_TYPE_SIZE);
    read(data.data(), data.size());
    return encoder.decode_action_type(data);
}

void ActionsProtocol::send_element(const std::shared_ptr<Action>& action) {
    ActionType type = action->get_type();

    switch (type) {
        case CREATE_REQUEST:
            return send_create_action(action);
        case JOIN_REQUEST:
            return send_join_action(action);
    }
    throw std::runtime_error("ActionsProtocol try to send unknown action");
}

void ActionsProtocol::send_create_action(const std::shared_ptr<Action>& action) {
    std::vector<int8_t> data(SEND_CREATE_SIZE);
    size_t offset = 0;
    encoder.encode_action_type(action->get_type(), &data[offset]);
    send(data.data(), SEND_CREATE_SIZE);
}

void ActionsProtocol::send_join_action(const std::shared_ptr<Action>& action) {
    std::vector<int8_t> data(SEND_JOIN_SIZE);
    size_t offset = 0;
    offset += encoder.encode_action_type(action->get_type(), &data[offset]);
    encoder.encode_game_code(action->get_game_code(), &data[offset]);
    send(data.data(), data.size());
}
