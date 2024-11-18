//
// Created by fran on 22/10/24.
//

#include "events_protocol.h"
#include "common/events/broadcast.h"
#include "common/events/connection/game_creation.h"
#include "common/events/connection/game_join.h"
#include "common/events/connection/refresh_games.h"
#include "common/events/connection/new_player.h"
#include "common/events/connection/start_game.h"
#include "common/events/map.h"
#include "common/events/tile.h"
#include <list>
#include <iostream>

#define EVENT_TYPE_SIZE sizeof(int8_t)
#define PLAYERS_ID_SIZE sizeof(uint16_t)
#define GAME_CODE_SIZE sizeof(uint32_t)
#define CONNECTED_SIZE sizeof(uint8_t)
#define MAX_PLAYER_SIZE sizeof(uint8_t)
#define ACTUAL_PLAYER_SIZE sizeof(uint8_t)


#define COORDINATE_SIZE sizeof(int16_t)
#define LEN_SIZE sizeof(uint8_t)
#define PLAYER_COORDINATE sizeof(int16_t)
#define PLAYER_IS_RIGHT_SIZE sizeof(uint8_t)
#define PLAYER_STATE_SIZE sizeof(uint8_t)


#define WEAPONS_SIZE (sizeof(uint8_t) + COORDINATE_SIZE * 2 + sizeof(uint8_t))
#define HEALTH_SIZE sizeof(uint8_t)
#define CHESTPLATE_SIZE sizeof(uint8_t)

#define GAME_ROOM_SIZE (MAX_PLAYER_SIZE + ACTUAL_PLAYER_SIZE + GAME_CODE_SIZE)

#define READ_NEW_PLAYER_SIZE (ACTUAL_PLAYER_SIZE + MAX_PLAYER_SIZE)

#define READ_CREATE_GAME_SIZE                                                  \
  (GAME_CODE_SIZE + 2 * PLAYERS_ID_SIZE + ACTUAL_PLAYER_SIZE + MAX_PLAYER_SIZE)

#define READ_JOIN_GAME_SIZE (2 * PLAYERS_ID_SIZE + CONNECTED_SIZE + ACTUAL_PLAYER_SIZE + MAX_PLAYER_SIZE)

#define READ_PLAYER_SIZE ( \
    2 * PLAYER_COORDINATE + PLAYERS_ID_SIZE + \
    PLAYER_STATE_SIZE + PLAYER_IS_RIGHT_SIZE +\
    WEAPONS_SIZE + HEALTH_SIZE + CHESTPLATE_SIZE)

#define READ_TILE_SIZE (COORDINATE_SIZE * 3 + sizeof(uint8_t))


#define SEND_CREATE_GAME_SIZE                                                  \
  (READ_CREATE_GAME_SIZE + EVENT_TYPE_SIZE)

#define SEND_JOIN_GAME_SIZE                                                    \
  (READ_JOIN_GAME_SIZE + EVENT_TYPE_SIZE)

#define SEND_PLAYER_SIZE READ_PLAYER_SIZE

#define SEND_TILE_SIZE READ_TILE_SIZE

#define SEND_NEW_PLAYER_SIZE (READ_NEW_PLAYER_SIZE + EVENT_TYPE_SIZE)

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

        case REFRESH_GAMES:
            return send_refresh(event);

        case NEW_PLAYER:
            return send_new_player(event);

        case START_GAME:
            return send_start_game(event);
        
        case MAP_LOAD:
            return send_map(event);

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
    int actual_players = encoder.decode_actual_players(data);
    int max_players = encoder.decode_max_players(data);
    return std::make_shared<GameCreation>(game_code, player_id_1, player_id_2, actual_players, max_players);
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
    EventType event = read_event_type();
    switch (event) {
        case CREATE_GAME: {
            return read_create();
        }
        case JOIN_GAME: {
            return read_join();
        }
        case BROADCAST:
            return read_broadcast();

        case REFRESH_GAMES:
            return read_refresh_game();

        case NEW_PLAYER:
            return read_new_player();

        case START_GAME:
            return std::make_shared<StartGame>();
        
        case MAP_LOAD:
            return read_map();
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
    offset += encoder.encode_connected(event->is_connected(), &data[offset]);
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
    offset += encoder.encode_actual_players(event->get_actual_players(), &data[offset]);
    offset += encoder.encode_max_players(event->get_max_players(), &data[offset]);
    send(data.data(), SEND_CREATE_GAME_SIZE);
}

std::shared_ptr<Event> EventsProtocol::read_broadcast() {
    std::vector<int8_t> data(LEN_SIZE);
    read(data.data(), data.size());
    int players_len = encoder.decode_len(data);

    std::vector<int8_t> players_data(players_len * READ_PLAYER_SIZE);
    read(players_data.data(), players_data.size());

    std::list<PlayerDTO> players;
    for (int i = 0; i < players_len; i++) {
        int player_id = encoder.decode_player_id(players_data);
        int x = encoder.decode_coordinate(players_data);
        int y = encoder.decode_coordinate(players_data);
        bool is_right = encoder.decode_is_right(players_data);
        State state = encoder.decode_player_state(players_data);

        WeaponDTO weapon = read_weapon(players_data);
        HelmetDTO helmet = read_helmet(players_data);
        Chestplate chestplate = read_chestplate(players_data);

        players.emplace_back(player_id, x, y, is_right, state, weapon, helmet, chestplate);
    }

    return std::make_shared<Broadcast>(std::move(players), std::list<BulletDTO>(), std::list<CrateDTO>(),
                                       std::list<WeaponDTO>(), std::list<Explosion>());
}

void EventsProtocol::send_broadcast(const std::shared_ptr<Event> &event) {
    std::vector<int8_t> data(LEN_SIZE +
                             event->get_players().size() * SEND_PLAYER_SIZE +
                             EVENT_TYPE_SIZE);
    size_t offset = 0;
    offset += encoder.encode_event_type(event->get_type(), &data[offset]);
    offset += encoder.encode_len(event->get_players().size(), &data[offset]);

    add_players(event, data, offset); // increase offset inplace
    send(data.data(), data.size());
}

WeaponDTO EventsProtocol::read_weapon(std::vector<int8_t> &data) {
    auto weapon_id = WeaponId(encoder.decode_id(data));
    int x = encoder.decode_coordinate(data);
    int y = encoder.decode_coordinate(data);
    bool shooting = encoder.decode_bool(data);
    return {weapon_id, x, y, shooting};
}

void EventsProtocol::add_weapon(std::vector<int8_t> &data, WeaponDTO weapon, size_t &offset) {
    offset += encoder.encode_id(weapon.get_id(), &data[offset]);
    offset += encoder.encode_coordinate(weapon.get_position_x(), &data[offset]);
    offset += encoder.encode_coordinate(weapon.get_position_y(), &data[offset]);
    offset += encoder.encode_bool(weapon.is_shooting(), &data[offset]);
}


HelmetDTO EventsProtocol::read_helmet(std::vector<int8_t> &data) {
    auto helmet_id = HelmetId(encoder.decode_id(data));
    return {helmet_id};
}

void EventsProtocol::add_health(std::vector<int8_t> &data, HelmetDTO helmet, size_t &offset) {
    offset += encoder.encode_id(helmet.get_id(), &data[offset]);
}

Chestplate EventsProtocol::read_chestplate(std::vector<int8_t> &data) {
    bool equipped = encoder.decode_bool(data);
    return {equipped};
}

void EventsProtocol::add_chestplate(std::vector<int8_t> &data, Chestplate chestplate, size_t &offset) {
    offset += encoder.encode_bool(chestplate.is_equipped(), &data[offset]);
}

void EventsProtocol::add_players(const std::shared_ptr<Event> &event, std::vector<int8_t> &data, size_t &offset) {
    for (const auto &player: event->get_players()) {
        offset += encoder.encode_player_id(player.get_player_id(), &data[offset]);
        offset += encoder.encode_coordinate(player.get_position_x(), &data[offset]);
        offset += encoder.encode_coordinate(player.get_position_y(), &data[offset]);
        offset += encoder.encode_is_right(player.is_right(), &data[offset]);
        offset += encoder.encode_player_state(player.get_state(), &data[offset]);

        // increase offset inplace
        add_weapon(data, player.get_weapon(), offset);
        add_health(data, player.get_helmet(), offset);
        add_chestplate(data, player.get_chestplate(), offset);

    }
}

void EventsProtocol::send_refresh(const std::shared_ptr<Event> &event) {
    std::vector<int8_t> data(LEN_SIZE + event->get_games().size() * GAME_ROOM_SIZE + EVENT_TYPE_SIZE);
    size_t offset = 0;
    offset += encoder.encode_event_type(event->get_type(), &data[offset]);
    offset += encoder.encode_len(event->get_games().size(), &data[offset]);

    for (const auto &game: event->get_games()) {
        offset += encoder.encode_game_code(game.get_game_code(), &data[offset]);
        offset += encoder.encode_actual_players(game.get_actual_players(), &data[offset]);
        offset += encoder.encode_max_players(game.get_max_players(), &data[offset]);
    }
    send(data.data(), data.size());
}

std::shared_ptr<Event> EventsProtocol::read_refresh_game() {
    std::vector<int8_t> data(LEN_SIZE);
    read(data.data(), data.size());
    int len = encoder.decode_len(data);

    std::vector<int8_t> game_rooms(len * GAME_ROOM_SIZE);
    read(game_rooms.data(), game_rooms.size());

    std::list<GameRoom> games;
    for (int i = 0; i < len; i++) {
        int game_code = encoder.decode_game_code(game_rooms);
        int actual_players = encoder.decode_actual_players(game_rooms);
        int max_players = encoder.decode_max_players(game_rooms);
        games.emplace_back(game_code, actual_players, max_players);
    }

    return std::make_shared<Refresh>(std::move(games));
}

void EventsProtocol::send_new_player(const std::shared_ptr<Event> &event) {
    std::vector<int8_t> data(SEND_NEW_PLAYER_SIZE);
    size_t offset = 0;
    offset += encoder.encode_event_type(event->get_type(), &data[offset]);
    offset += encoder.encode_actual_players(event->get_actual_players(), &data[offset]);
    offset += encoder.encode_max_players(event->get_max_players(), &data[offset]);
    send(data.data(), data.size());
}

std::shared_ptr<Event> EventsProtocol::read_new_player() {
    std::vector<int8_t> data(READ_NEW_PLAYER_SIZE);
    read(data.data(), data.size());
    int actual_players = encoder.decode_actual_players(data);
    int max_players = encoder.decode_max_players(data);
    return std::make_shared<NewPlayer>(actual_players, max_players);
}

void EventsProtocol::send_start_game(const std::shared_ptr<Event> &event) {
    std::vector<int8_t> data(EVENT_TYPE_SIZE);
    size_t offset = 0;
    offset += encoder.encode_event_type(event->get_type(), &data[offset]);
    send(data.data(), data.size());
}

std::shared_ptr<Event> EventsProtocol::read_map() {
    std::vector<int8_t> data(LEN_SIZE);
    read(data.data(), data.size());
    int tiles_len = encoder.decode_len(data);

    std::vector<int8_t> tiles_data(tiles_len * READ_TILE_SIZE + COORDINATE_SIZE * 2 + sizeof(uint8_t));
    read(tiles_data.data(), tiles_data.size());

    std::list<Tile> tiles;
    for (int i = 0; i < tiles_len; i++) {
        int start_x = encoder.decode_coordinate(tiles_data);
        int end_x = encoder.decode_coordinate(tiles_data);
        int y = encoder.decode_coordinate(tiles_data);
        int tile_id = encoder.decode_tile_id(tiles_data);
        tiles.emplace_back(start_x, end_x, y, tile_id);
    }
    int background_id = encoder.decode_background_id(tiles_data);
    int width = encoder.decode_coordinate(tiles_data);
    int length = encoder.decode_coordinate(tiles_data);
    std::cout << data.size() << std::endl;
    
    return std::make_shared<MapDTO>(std::move(tiles), background_id, width, length);
}

void EventsProtocol::send_map(const std::shared_ptr<Event> &event) {
    std::vector<int8_t> data(LEN_SIZE +
                             event->get_platforms().size() * SEND_TILE_SIZE +
                             EVENT_TYPE_SIZE + COORDINATE_SIZE * 3 + sizeof(uint8_t));
    size_t offset = 0;
    offset += encoder.encode_event_type(event->get_type(), &data[offset]);
    offset += encoder.encode_len(event->get_platforms().size(), &data[offset]);

    add_platforms(event, data, offset);
    offset += encoder.encode_background_id(event->get_background_id(), &data[offset]);
    offset += encoder.encode_coordinate(event->get_width(), &data[offset]);
    offset += encoder.encode_coordinate(event->get_length(), &data[offset]);
    send(data.data(), data.size());
}

void EventsProtocol::add_platforms(const std::shared_ptr<Event> &event, std::vector<int8_t> &data, size_t &offset) {
    for (const auto &platform: event->get_platforms()) {
        offset += encoder.encode_coordinate(platform.get_start_x(), &data[offset]);
        offset += encoder.encode_coordinate(platform.get_end_x(), &data[offset]);
        offset += encoder.encode_coordinate(platform.get_end_x(), &data[offset]);
        offset += encoder.encode_tile_id(platform.get_tile_id(), &data[offset]);
    }
}



