//
// Created by fran on 22/10/24.
//

#include "events_protocol.h"
#include "common/events/game_creation.h"
#include "common/events/game_join.h"

#define EVENT_TYPE_SIZE sizeof(int8_t)
#define PLAYERS_IDS_SIZE (2*sizeof(uint16_t))
#define GAME_CODE_SIZE sizeof(uint32_t)
#define CONNECTED_SIZE sizeof(uint8_t)

#define READ_CREATE_GAME_SIZE (GAME_CODE_SIZE + PLAYERS_IDS_SIZE + CONNECTED_SIZE)

#define READ_JOIN_GAME_SIZE (PLAYERS_IDS_SIZE + CONNECTED_SIZE)

#define SEND_CREATE_GAME_SIZE (GAME_CODE_SIZE + PLAYERS_IDS_SIZE + CONNECTED_SIZE + EVENT_TYPE_SIZE)
#define SEND_JOIN_GAME_SIZE (PLAYERS_IDS_SIZE + CONNECTED_SIZE + EVENT_TYPE_SIZE)


EventsProtocol::EventsProtocol(Socket* socket, Encoder encoder) : Protocol(socket), encoder(encoder) {}


void EventsProtocol::send_element(std::shared_ptr<Event> &event) {
    switch (event->get_type()) {
        case CREATE_GAME: {
            return send_create(event);
        }
        case JOIN_GAME: {
            return send_join(event);
        }
        default:
            throw std::runtime_error("Tipo de evento no soportado.");
    }
}

EventType EventsProtocol::read_event_type() {
    std::vector<int8_t> data(EVENT_TYPE_SIZE);
    read(data.data(), data.size());
    return encoder.decode_event_type(data);
}

std::shared_ptr<Event> EventsProtocol::read_create() {
    std::vector<int8_t> data(READ_CREATE_GAME_SIZE);
    read(data.data(), data.size());
    int game_code = encoder.decode_game_code(data);
    int player_id_1 = encoder.decode_player_id(data);
    int player_id_2 = encoder.decode_player_id(data);
    return std::make_shared<GameCreation>(game_code, player_id_1, player_id_2);
}

std::shared_ptr<Event> EventsProtocol::read_join() {
    std::vector<int8_t> data(READ_JOIN_GAME_SIZE);
    read(data.data(), data.size());
    int player_id_1 = encoder.decode_player_id(data);
    int player_id_2 = encoder.decode_player_id(data);
    bool is_connected = encoder.decode_connected(data);
    return std::make_shared<GameJoin>(player_id_1, player_id_2, is_connected);
}

std::shared_ptr<Event> EventsProtocol::read_element() {
    switch (read_event_type()) {
        case CREATE_GAME: {
            return read_create();
        }
        case JOIN_GAME: {
            return read_join();
        }
        default:
            throw std::runtime_error("Tipo de evento no soportado.");
    }
}
void EventsProtocol::send_join(const std::shared_ptr<Event> &event) {
    std::vector<int8_t> data(SEND_JOIN_GAME_SIZE);
    size_t offset = 0;
    offset += encoder.encode_event_type(event->get_type(), &data[offset]);
    offset += encoder.encode_player_id(event->get_player_id_1(), &data[offset]);
    offset += encoder.encode_player_id(event->get_player_id_2(), &data[offset]);
    encoder.encode_connected(event->is_connected(), &data[offset]);
    send(data.data(), SEND_JOIN_GAME_SIZE);
}

void EventsProtocol::send_create(const std::shared_ptr<Event> &event) {
    std::vector<int8_t> data(SEND_CREATE_GAME_SIZE);
    size_t offset = 0;
    offset += encoder.encode_event_type(event->get_type(), &data[offset]);
    offset += encoder.encode_game_code(event->get_game_code(), &data[offset]);
    offset += encoder.encode_player_id(event->get_player_id_1(), &data[offset]);
    offset += encoder.encode_player_id(event->get_player_id_2(), &data[offset]);
    encoder.encode_connected(event->is_connected(), &data[offset]);
    send(data.data(), SEND_CREATE_GAME_SIZE);
}

