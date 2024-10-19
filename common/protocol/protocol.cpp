#include "common/protocol/protocol.h"

#include <stdexcept>
#include <utility>

#include <netinet/in.h>

#include "common/protocol/action_macros.h"
#include "common/protocol/protocol_error.h"
#include "common/socket/liberror.h"

#define READ_BROADCAST_SIZE (sizeof(int8_t))

Protocol::Protocol(Socket *socket, Encoder encoder)
        : socket(socket), is_closed(false), encoder(encoder) {}

Action Protocol::read_message() {

    return Action(ACTION_BROADCAST);
}

Action Protocol::read_action() {
    std::string action_name = encoder.decode_action_name(read_action_code());
    if (action_name == ACTION_ATTACK) {
        return Action(ACTION_ATTACK);
    } else if (action_name == ACTION_BROADCAST) {
        return read_message();
    }
    throw std::runtime_error("protocol try to action_read invalid action.");
}

int8_t Protocol::read_action_code() {
    int8_t code;
    read(&code, sizeof(int8_t));
    return code;
}

void Protocol::read(void *data, size_t size) {
    if (is_closed) {
        throw ProtocolError("protocol was closed. Cannot read data.");
    }
    bool was_closed = false;
    socket->recvall(data, size, &was_closed);
    if (was_closed) {
        is_closed = true;
        throw ProtocolError("protocol was closed when reading data");
    }
}

void Protocol::send_attack(const Action &action) {
    int8_t code = encoder.encode_action_name(action.get_name());
    send(&code, sizeof(int8_t));
}

void Protocol::send_broadcast(const Action &action) {
    std::vector<int8_t> buffer;
    buffer.push_back(encoder.encode_action_name(action.get_name()));

    send(buffer.data(), buffer.size());
}

void Protocol::send_action(const Action &action) {
    if (action.is_attack()) {
        send_attack(action);
        return;
    } else if (action.is_broadcast()) {
        send_broadcast(action);
        return;
    }
    throw std::runtime_error("protocol try to send unknown action");
}

void Protocol::send(void *data, size_t size) {
    if (is_closed) {
        throw ProtocolError("protocol is closed. Cannot send data.");
    }
    bool was_closed = false;
    socket->sendall(data, size, &was_closed);
    if (was_closed) {
        is_closed = true;
        throw ProtocolError("protocol was closed when sending data");
    }
}

bool Protocol::is_open() { return !is_closed; }

void Protocol::send_game_code(uint32_t game_code, uint16_t player_id) {
    try {
        uint32_t code = htonl(game_code);
        send(&code, sizeof(code));
        uint16_t id = htons(player_id);
        send(&id, sizeof(id));
    } catch (const LibError &e) {
        throw ProtocolError("protocol was closed when sending game code");
    }
}

void Protocol::send_game_code(uint32_t game_code) {
    try {
        uint32_t code = htonl(game_code);
        send(&code, sizeof(code));
    } catch (const LibError &e) {
        throw ProtocolError("protocol was closed when sending game code");
    }
}

void Protocol::read_game_data(uint32_t &game_code, uint16_t &player_id) {
    try {
        game_code = read_game_code();
        player_id = read_player_id();

    } catch (const LibError &e) {
        throw ProtocolError("protocol was closed when reading game code");
    }
}

uint16_t Protocol::read_player_id() {
    uint16_t id;
    read(&id, sizeof(id));

    return ntohs(id);
}

uint32_t Protocol::read_game_code() {
    uint32_t code;
    try {
        read(&code, sizeof(code));
    } catch (const LibError &e) {
        throw ProtocolError("protocol was closed when reading game code");
    }
    return ntohl(code);
}
