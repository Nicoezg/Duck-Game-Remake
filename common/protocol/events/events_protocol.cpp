//
// Created by fran on 22/10/24.
//

#include "events_protocol.h"
#include "common/events/broadcast.h"
#include "common/events/game_creation.h"
#include "common/events/game_join.h"
#include "common/events/player.h"
#include <list>

#define EVENT_TYPE_SIZE sizeof(int8_t)
#define PLAYERS_ID_SIZE sizeof(uint16_t)
#define GAME_CODE_SIZE sizeof(uint32_t)
#define CONNECTED_SIZE sizeof(uint8_t)
#define MAX_PLAYER_SIZE sizeof(uint8_t)
#define ACTUAL_PLAYER_SIZE sizeof(uint8_t)


#define PLAYERS_LEN_SIZE sizeof(uint8_t)
#define PLAYER_COORDINATE sizeof(int16_t)
#define PLAYER_IS_RIGHT_SIZE sizeof(uint8_t)
#define PLAYER_STATE_SIZE sizeof(uint8_t)

#define READ_CREATE_GAME_SIZE                                                  \
  (GAME_CODE_SIZE + 2 * PLAYERS_ID_SIZE + MAX_PLAYER_SIZE)

#define READ_JOIN_GAME_SIZE (2 * PLAYERS_ID_SIZE + CONNECTED_SIZE + ACTUAL_PLAYER_SIZE + MAX_PLAYER_SIZE)

#define READ_PLAYER_SIZE (2 * PLAYER_COORDINATE + PLAYERS_ID_SIZE + PLAYER_STATE_SIZE + PLAYER_IS_RIGHT_SIZE)

#define SEND_CREATE_GAME_SIZE                                                  \
  (GAME_CODE_SIZE + 2 * PLAYERS_ID_SIZE + EVENT_TYPE_SIZE + MAX_PLAYER_SIZE)

#define SEND_JOIN_GAME_SIZE                                                    \
  (2 * PLAYERS_ID_SIZE + CONNECTED_SIZE + EVENT_TYPE_SIZE + ACTUAL_PLAYER_SIZE + MAX_PLAYER_SIZE)

#define SEND_PLAYER_SIZE (2 * PLAYER_COORDINATE + PLAYERS_ID_SIZE + PLAYER_STATE_SIZE + PLAYER_IS_RIGHT_SIZE)

EventsProtocol::EventsProtocol(Socket *socket, Encoder encoder)
        : Protocol(socket), encoder(encoder) {}

void EventsProtocol::send_element(std::shared_ptr<Event> &event) {
    switch (event->get_type()) {
        case CREATE_GAME: {
            return send_create(event);
        }
        case JOIN_GAME: {
            return send_join(event);
        }
        case BROADCAST:
            return send_broadcast(event);
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
    int max_players = encoder.decode_max_players(data);
    return std::make_shared<GameCreation>(game_code, player_id_1, player_id_2, max_players);
}

std::shared_ptr<Event> EventsProtocol::read_join() {
    std::vector<int8_t> data(READ_JOIN_GAME_SIZE);
    read(data.data(), data.size());
    int player_id_1 = encoder.decode_player_id(data);
    int player_id_2 = encoder.decode_player_id(data);
    bool is_connected = encoder.decode_connected(data);
    int actual_players = encoder.decode_actual_players(data);
    int max_players = encoder.decode_max_players(data);
    return std::make_shared<GameJoin>(player_id_1, player_id_2, is_connected, actual_players, max_players);
}

std::shared_ptr<Event> EventsProtocol::read_element() {
    switch (read_event_type()) {
        case CREATE_GAME: {
            return read_create();
        }
        case JOIN_GAME: {
            return read_join();
        }
        case BROADCAST:
            return read_broadcast();
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
    offset +=encoder.encode_connected(event->is_connected(), &data[offset]);
    offset += encoder.encode_actual_players(event->get_actual_players(), &data[offset]);
    offset += encoder.encode_max_players(event->get_max_players(), &data[offset]);
    send(data.data(), SEND_JOIN_GAME_SIZE);
}

void EventsProtocol::send_create(const std::shared_ptr<Event> &event) {
    std::vector<int8_t> data(SEND_CREATE_GAME_SIZE);
    size_t offset = 0;
    offset += encoder.encode_event_type(event->get_type(), &data[offset]);
    offset += encoder.encode_game_code(event->get_game_code(), &data[offset]);
    offset += encoder.encode_player_id(event->get_player_id_1(), &data[offset]);
    offset += encoder.encode_player_id(event->get_player_id_2(), &data[offset]);
    offset += encoder.encode_max_players(event->get_max_players(), &data[offset]);
    send(data.data(), SEND_CREATE_GAME_SIZE);
}

std::shared_ptr<Event> EventsProtocol::read_broadcast() {
    std::vector<int8_t> data(PLAYERS_LEN_SIZE);
    read(data.data(), data.size());
    int players_len = encoder.decode_players_len(data);

    std::vector<int8_t> players_data(players_len * READ_PLAYER_SIZE);
    read(players_data.data(), players_data.size());

    std::list<Player> players;
    for (int i = 0; i < players_len; i++) {
        int player_id = encoder.decode_player_id(players_data);
        int x = encoder.decode_coordinate(players_data);
        int y = encoder.decode_coordinate(players_data);
        bool is_right = encoder.decode_is_right(players_data);
        State state = encoder.decode_player_state(players_data);

        players.emplace_back(player_id, x, y, is_right, state);
    }

    return std::make_shared<Broadcast>(std::move(players));
}

void EventsProtocol::send_broadcast(const std::shared_ptr<Event> &event) {
    std::vector<int8_t> data(PLAYERS_LEN_SIZE +
                             event->get_players().size() * SEND_PLAYER_SIZE +
                             EVENT_TYPE_SIZE);
    size_t offset = 0;
    offset += encoder.encode_event_type(event->get_type(), &data[offset]);
    offset +=
            encoder.encode_players_len(event->get_players().size(), &data[offset]);

    for (const auto &player: event->get_players()) {
        offset += encoder.encode_player_id(player.get_player_id(), &data[offset]);
        offset += encoder.encode_coordinate(player.get_position_x(), &data[offset]);
        offset += encoder.encode_coordinate(player.get_position_y(), &data[offset]);
        offset += encoder.encode_is_right(player.is_right(), &data[offset]);
        offset += encoder.encode_player_state(player.get_state(), &data[offset]);
    }
    send(data.data(), data.size());
}
