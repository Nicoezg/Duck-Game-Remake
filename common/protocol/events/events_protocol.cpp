//
// Created by fran on 22/10/24.
//

#include "events_protocol.h"
#include "common/events/broadcast.h"
#include "common/events/connection/game_creation.h"
#include "common/events/connection/game_join.h"
#include "common/events/connection/new_player.h"
#include "common/events/connection/refresh_games.h"
#include "common/events/connection/start_game.h"
#include "common/events/map.h"
#include "common/events/tile.h"
#include "common/events/game_over.h"
#include <cstddef>
#include <iostream>
#include <list>

EventsProtocol::EventsProtocol(Socket *socket, Encoder encoder)
        : Protocol(socket), encoder(encoder) {}

void EventsProtocol::send_element(Event &event) {
    switch (event.get_type()) {
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

        case GAME_OVER:
            return send_game_over(event);

        default:
            throw std::runtime_error("Tipo de evento no soportado.");
    }
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

        case GAME_OVER:
            return read_game_over();
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
    int player_id_1 = encoder.decode_player_id(data);
    int player_id_2 = encoder.decode_player_id(data);
    GameRoom game_room = read_game_room();
    std::list<PlayerData> players_data = read_players_data();
    return std::make_shared<GameCreation>(game_room, player_id_1, player_id_2, players_data);
}

std::shared_ptr<Event> EventsProtocol::read_join() {
    std::vector<int8_t> data(READ_JOIN_GAME_SIZE);
    read(data.data(), data.size());
    int player_id_1 = encoder.decode_player_id(data);
    int player_id_2 = encoder.decode_player_id(data);
    bool is_connected = encoder.decode_bool(data);
    GameRoom game_room = read_game_room();
    std::list<PlayerData> players_data = read_players_data();
    return std::make_shared<GameJoin>(player_id_1, player_id_2, is_connected, game_room, players_data);
}

void EventsProtocol::send_join(const Event &event) {
    size_t size_to_send = get_size_to_send(event, SEND_JOIN_GAME_SIZE);
    std::vector<int8_t> data(size_to_send);
    size_t offset = 0;
    offset += encoder.encode_event_type(event.get_type(), &data[offset]);
    offset += encoder.encode_player_id(event.get_player_id_1(), &data[offset]);
    offset += encoder.encode_player_id(event.get_player_id_2(), &data[offset]);
    offset += encoder.encode_bool(event.is_connected(), &data[offset]);
    add_game_room(event.get_game_room(), data, offset);
    add_players_data(data, offset, event.get_players_data());
    send(data.data(), data.size());
}

size_t EventsProtocol::get_size_to_send(const Event &event, size_t start) {
    int game_room_size = GAME_ROOM_SIZE + event.get_game_room().get_game_name().size();
    int players_data_size = LEN_SIZE;
    for (const auto &player_data: event.get_players_data()) {
        players_data_size += PLAYER_DATA_SIZE + player_data.get_name().size();
    }
    return start + game_room_size + players_data_size;
}

void EventsProtocol::send_create(const Event &event) {
    size_t size_to_send = get_size_to_send(event, SEND_CREATE_GAME_SIZE);
    std::vector<int8_t> data(size_to_send);
    size_t offset = 0;
    offset += encoder.encode_event_type(event.get_type(), &data[offset]);
    offset += encoder.encode_player_id(event.get_player_id_1(), &data[offset]);
    offset += encoder.encode_player_id(event.get_player_id_2(), &data[offset]);
    add_game_room(event.get_game_room(), data, offset);
    add_players_data(data, offset, event.get_players_data());
    send(data.data(), data.size());
}

std::shared_ptr<Event> EventsProtocol::read_broadcast() {
    std::vector<int8_t> size_player_data(LEN_SIZE);
    read(size_player_data.data(), size_player_data.size());
    int players_len = encoder.decode_len(size_player_data);

    std::vector<int8_t> players_data(players_len * READ_PLAYER_SIZE);
    read(players_data.data(), players_data.size());

    std::list<PlayerDTO> players;
    for (int i = 0; i < players_len; i++) {
        int player_id = encoder.decode_player_id(players_data);
        int x = encoder.decode_coordinate(players_data);
        int y = encoder.decode_coordinate(players_data);
        bool is_right = encoder.decode_bool(players_data);
        State state = encoder.decode_player_state(players_data);

        WeaponDTO weapon = read_weapon(players_data);
        HelmetDTO helmet = read_helmet(players_data);
        Chestplate chestplate = read_chestplate(players_data);

        players.emplace_back(player_id, x, y, is_right, state, weapon, helmet,
                             chestplate);
    }

    std::vector<int8_t> size_bullet_data(LEN_SIZE);
    read(size_bullet_data.data(), size_bullet_data.size());
    int bullets_len = encoder.decode_len(size_bullet_data);

    std::vector<int8_t> bullets_data(bullets_len * READ_BULLET_SIZE);
    read(bullets_data.data(), bullets_data.size());

    std::list<BulletDTO> bullets;
    for (int i = 0; i < bullets_len; i++) {
        int id = encoder.decode_id(bullets_data);
        int x = encoder.decode_coordinate(bullets_data);
        int y = encoder.decode_coordinate(bullets_data);
        float angle = encoder.decode_angle(bullets_data);
        bool direction = encoder.decode_bool(bullets_data);
        bullets.emplace_back(x, y, BulletId(id), angle, direction);
    }

    std::vector<int8_t> size_crates_data(LEN_SIZE);
    read(size_crates_data.data(), size_crates_data.size());
    int crates_len = encoder.decode_len(size_crates_data);

    std::vector<int8_t> crates_data(crates_len * READ_CRATE_SIZE);
    read(crates_data.data(), crates_data.size());

    std::list<CrateDTO> crates;
    for (int i = 0; i < crates_len; i++) {
        int x = encoder.decode_coordinate(crates_data);
        int y = encoder.decode_coordinate(crates_data);
        uint8_t hp = encoder.decode_bool(crates_data);
        bool is_hit = encoder.decode_bool(crates_data);
        crates.emplace_back(x, y, hp, is_hit);
    }

    std::vector<int8_t> size_item_spawns_data(LEN_SIZE);
    read(size_item_spawns_data.data(), size_item_spawns_data.size());
    int item_spawns_len = encoder.decode_len(size_item_spawns_data);

    std::vector<int8_t> item_spawns_data(item_spawns_len * READ_ITEM_SPAWN_SIZE);
    read(item_spawns_data.data(), item_spawns_data.size());

    std::list<ItemSpawnDTO> item_spawns;
    for (int i = 0; i < item_spawns_len; i++) {
        auto item_spawn_id = ItemSpawnId(encoder.decode_id(item_spawns_data));
        int x = encoder.decode_coordinate(item_spawns_data);
        int y = encoder.decode_coordinate(item_spawns_data);
        item_spawns.emplace_back(item_spawn_id, x, y);
    }

    std::vector<int8_t> size_explosions_data(LEN_SIZE);
    read(size_explosions_data.data(), size_explosions_data.size());
    int explosions_len = encoder.decode_len(size_explosions_data);

    std::vector<int8_t> explosions_data(explosions_len * READ_EXPLOSION_SIZE);
    read(explosions_data.data(), explosions_data.size());

    std::list<ExplosionDTO> explosions;
    for (int i = 0; i < explosions_len; i++) {
        int x = encoder.decode_coordinate(explosions_data);
        int y = encoder.decode_coordinate(explosions_data);
        uint8_t current_duration = encoder.decode_id(explosions_data);
        explosions.emplace_back(x, y, current_duration);
    }

    std::vector<int8_t> size_throwables_data(LEN_SIZE);
    read(size_throwables_data.data(), size_throwables_data.size());
    int throwables_len = encoder.decode_len(size_throwables_data);

    std::vector<int8_t> throwables_data(throwables_len * READ_THROWABLE_SIZE);
    read(throwables_data.data(), throwables_data.size());

    std::list<ThrowableDTO> throwables;
    for (int i = 0; i < throwables_len; i++) {
        int id = encoder.decode_id(throwables_data);
        int x = encoder.decode_coordinate(throwables_data);
        int y = encoder.decode_coordinate(throwables_data);
        float angle = encoder.decode_angle(throwables_data);
        bool direction = encoder.decode_bool(throwables_data);
        bool action = encoder.decode_bool(throwables_data);
        throwables.emplace_back(x, y, ThrowableId(id), angle, direction, action);
    }

    return std::make_shared<Broadcast>(
            std::move(players), std::move(bullets), std::move(crates),
            std::move(item_spawns), std::move(explosions), std::move(throwables));
}

void EventsProtocol::send_broadcast(const Event &event) {
    std::vector<int8_t> data(
            LEN_SIZE * 6 + event.get_players().size() * SEND_PLAYER_SIZE +
            event.get_bullets().size() * SEND_BULLET_SIZE + SEND_EXPLOSION_SIZE * event.get_explosions().size() +
            EVENT_TYPE_SIZE
            + event.get_crates().size() * SEND_CRATE_SIZE + event.get_item_spawns().size() * SEND_ITEM_SPAWN_SIZE
            + event.get_throwables().size() * SEND_THROWABLE_SIZE);
    size_t offset = 0;
    offset += encoder.encode_event_type(event.get_type(), &data[offset]);

    offset += encoder.encode_len(event.get_players().size(), &data[offset]);
    add_players(event, data, offset); // increase offset inplace

    offset += encoder.encode_len(event.get_bullets().size(), &data[offset]);
    add_bullets(event, data, offset);

    offset += encoder.encode_len(event.get_crates().size(), &data[offset]);
    add_crates(event, data, offset);

    offset += encoder.encode_len(event.get_item_spawns().size(), &data[offset]);
    add_item_spawns(event, data, offset);

    offset += encoder.encode_len(event.get_explosions().size(), &data[offset]);
    add_explosions(event, data, offset);

    offset += encoder.encode_len(event.get_throwables().size(), &data[offset]);
    add_throwables(event, data, offset);


    send(data.data(), data.size());
}

void EventsProtocol::add_bullets(const Event &event,
                                 std::vector<int8_t> &data, size_t &offset) {
    for (const auto &bullet: event.get_bullets()) {
        offset += encoder.encode_id(bullet.get_id(), &data[offset]);
        offset += encoder.encode_coordinate(bullet.get_position_x(), &data[offset]);
        offset += encoder.encode_coordinate(bullet.get_position_y(), &data[offset]);
        offset += encoder.encode_angle(bullet.get_angle(), &data[offset]);
        offset += encoder.encode_bool(bullet.get_direction(), &data[offset]);
    }
}

void EventsProtocol::add_crates(const Event &event,
                                std::vector<int8_t> &data, size_t &offset) {
    for (const auto &crate: event.get_crates()) {
        offset += encoder.encode_coordinate(crate.get_position_x(), &data[offset]);
        offset += encoder.encode_coordinate(crate.get_position_y(), &data[offset]);
        offset += encoder.encode_bool(crate.get_hp(), &data[offset]);
        offset += encoder.encode_bool(crate.was_hit(), &data[offset]);
    }
}

void EventsProtocol::add_item_spawns(const Event &event,
                                     std::vector<int8_t> &data, size_t &offset) {
    for (const auto &item_spawn: event.get_item_spawns()) {
        offset += encoder.encode_id(item_spawn.get_id(), &data[offset]);
        offset += encoder.encode_coordinate(item_spawn.get_position_x(),
                                            &data[offset]);
        offset += encoder.encode_coordinate(item_spawn.get_position_y(),
                                            &data[offset]);
    }
}

void EventsProtocol::add_explosions(const Event& event, std::vector<int8_t> &data, size_t &offset) {
    for (const auto &explosion: event.get_explosions()) {
        offset += encoder.encode_coordinate(explosion.get_position_x(),
                                            &data[offset]);
        offset += encoder.encode_coordinate(explosion.get_position_y(),
                                            &data[offset]);
        offset += encoder.encode_id(explosion.get_current_duration(), &data[offset]);
    }
}

void EventsProtocol::add_throwables(const Event &event,
                                    std::vector<int8_t> &data, size_t &offset) {
    for (const auto &throwable: event.get_throwables()) {
        offset += encoder.encode_id(throwable.get_id(), &data[offset]);
        offset += encoder.encode_coordinate(throwable.get_position_x(), &data[offset]);
        offset += encoder.encode_coordinate(throwable.get_position_y(), &data[offset]);
        offset += encoder.encode_angle(throwable.get_angle(), &data[offset]);
        offset += encoder.encode_bool(throwable.get_direction(), &data[offset]);
        offset += encoder.encode_bool(throwable.get_action(), &data[offset]);
    }
}

WeaponDTO EventsProtocol::read_weapon(std::vector<int8_t> &data) {
    auto weapon_id = WeaponId(encoder.decode_id(data));
    int x = encoder.decode_coordinate(data);
    int y = encoder.decode_coordinate(data);
    bool shooting = encoder.decode_bool(data);
    return {weapon_id, x, y, shooting};
}

void EventsProtocol::add_weapon(std::vector<int8_t> &data, WeaponDTO weapon,
                                size_t &offset) {
    offset += encoder.encode_id(weapon.get_id(), &data[offset]);
    offset += encoder.encode_coordinate(weapon.get_position_x(), &data[offset]);
    offset += encoder.encode_coordinate(weapon.get_position_y(), &data[offset]);
    offset += encoder.encode_bool(weapon.is_shooting(), &data[offset]);
}

/*void EventsProtocol::add_player_weapon(std::vector<int8_t> &data, PlayerDTO
player, size_t &offset) { WeaponDTO weapon = player.get_weapon(); offset +=
encoder.encode_id(weapon.get_id(), &data[offset]); offset +=
encoder.encode_coordinate(player.get_position_x(), &data[offset]); offset +=
encoder.encode_coordinate(player.get_position_y(), &data[offset]); offset +=
encoder.encode_bool(weapon.is_shooting(), &data[offset]);
}*/

HelmetDTO EventsProtocol::read_helmet(std::vector<int8_t> &data) {
    auto helmet_id = HelmetId(encoder.decode_id(data));
    return {helmet_id};
}

void EventsProtocol::add_health(std::vector<int8_t> &data, HelmetDTO helmet,
                                size_t &offset) {
    offset += encoder.encode_id(helmet.get_id(), &data[offset]);
}

Chestplate EventsProtocol::read_chestplate(std::vector<int8_t> &data) {
    bool equipped = encoder.decode_bool(data);
    return {equipped};
}

void EventsProtocol::add_chestplate(std::vector<int8_t> &data,
                                    Chestplate chestplate, size_t &offset) {
    offset += encoder.encode_bool(chestplate.is_equipped(), &data[offset]);
}

void EventsProtocol::add_players(const Event &event,
                                 std::vector<int8_t> &data, size_t &offset) {
    for (const auto &player: event.get_players()) {
        offset += encoder.encode_player_id(player.get_player_id(), &data[offset]);
        offset += encoder.encode_coordinate(player.get_position_x(), &data[offset]);
        offset += encoder.encode_coordinate(player.get_position_y(), &data[offset]);
        offset += encoder.encode_bool(player.is_right(), &data[offset]);
        offset += encoder.encode_player_state(player.get_state(), &data[offset]);

        // increase offset inplace
        add_weapon(data, player.get_weapon(), offset);
        add_health(data, player.get_helmet(), offset);
        add_chestplate(data, player.get_chestplate(), offset);
    }
}

void EventsProtocol::send_refresh(const Event &event) {
    size_t size_to_send = EVENT_TYPE_SIZE + LEN_SIZE;
    for (const auto &game: event.get_games()) {
        size_to_send += game.get_game_name().size() + GAME_ROOM_SIZE;
    }
    std::vector<int8_t> data(size_to_send);
    size_t offset = 0;
    offset += encoder.encode_event_type(event.get_type(), &data[offset]);
    offset += encoder.encode_len(event.get_games().size(), &data[offset]);
    for (const auto &game: event.get_games()) {
        add_game_room(game, data, offset);
    }
    send(data.data(), data.size());
}

std::shared_ptr<Event> EventsProtocol::read_refresh_game() {
    std::vector<int8_t> data(LEN_SIZE);
    read(data.data(), data.size());
    int len = encoder.decode_len(data);

    std::list<GameRoom> games;
    for (int i = 0; i < len; i++) {
        games.emplace_back(read_game_room());
    }

    return std::make_shared<Refresh>(std::move(games));
}

void EventsProtocol::send_new_player(const Event &event) {
    size_t size_to_send = SEND_NEW_PLAYER_SIZE + LEN_SIZE;
    for (const auto &player: event.get_players_data()) {
        size_to_send += PLAYER_DATA_SIZE + player.get_name().size();
    }
    std::vector<int8_t> data(size_to_send);
    size_t offset = 0;
    offset += encoder.encode_event_type(event.get_type(), &data[offset]);
    offset += encoder.encode_actual_players(event.get_actual_players(), &data[offset]);
    offset += encoder.encode_max_players(event.get_max_players(), &data[offset]);
    add_players_data(data, offset, event.get_players_data());

    send(data.data(), data.size());
}

std::shared_ptr<Event> EventsProtocol::read_new_player() {
    std::vector<int8_t> data(READ_NEW_PLAYER_SIZE);
    read(data.data(), data.size());
    int actual_players = encoder.decode_actual_players(data);
    int max_players = encoder.decode_max_players(data);
    std::list<PlayerData> players_data = read_players_data();
    return std::make_shared<NewPlayer>(actual_players, max_players, players_data);
}

void EventsProtocol::send_start_game(const Event &event) {
    std::vector<int8_t> data(EVENT_TYPE_SIZE);
    size_t offset = 0;
    offset += encoder.encode_event_type(event.get_type(), &data[offset]);
    send(data.data(), data.size());
}

std::shared_ptr<Event> EventsProtocol::read_map() {
    std::vector<int8_t> data(LEN_SIZE);
    read(data.data(), data.size());
    int tiles_len = encoder.decode_len(data);

    std::vector<int8_t> tiles_data(tiles_len * READ_TILE_SIZE + READ_BACKGROUND_SIZE);
    read(tiles_data.data(), tiles_data.size());

    std::list<Tile> tiles;
    for (int i = 0; i < tiles_len; i++) {
        tiles.emplace_back(read_tile(tiles_data));
    }
    int background_id = encoder.decode_background_id(tiles_data);
    int width = encoder.decode_coordinate(tiles_data);
    int length = encoder.decode_coordinate(tiles_data);

    return std::make_shared<MapDTO>(std::move(tiles), background_id, width, length);
}

Tile EventsProtocol::read_tile(std::vector<int8_t> &data) {
    int start_x = encoder.decode_coordinate(data);
    int end_x = encoder.decode_coordinate(data);
    int y = encoder.decode_coordinate(data);
    int tile_id = encoder.decode_tile_id(data);
    return {start_x, end_x, y, tile_id};
}

void EventsProtocol::send_map(const Event &event) {
    std::vector<int8_t> data(LEN_SIZE +
                             event.get_platforms().size() * SEND_TILE_SIZE +
                             EVENT_TYPE_SIZE + SEND_BACKGROUND_SIZE);
    size_t offset = 0;
    offset += encoder.encode_event_type(event.get_type(), &data[offset]);
    offset += encoder.encode_len(event.get_platforms().size(), &data[offset]);

    add_platforms(event, data, offset);
    offset += encoder.encode_background_id(event.get_background_id(), &data[offset]);
    offset += encoder.encode_coordinate(event.get_width(), &data[offset]);
    offset += encoder.encode_coordinate(event.get_length(), &data[offset]);
    send(data.data(), data.size());
}

void EventsProtocol::add_platforms(const Event &event,
                                   std::vector<int8_t> &data, size_t &offset) {
    for (const auto &platform: event.get_platforms()) {
        offset += encoder.encode_coordinate(platform.get_start_x(), &data[offset]);
        offset += encoder.encode_coordinate(platform.get_end_x(), &data[offset]);
        offset += encoder.encode_coordinate(platform.get_y(), &data[offset]);
        offset += encoder.encode_tile_id(platform.get_tile_id(), &data[offset]);
    }
}


void EventsProtocol::send_game_over(const Event &event) {
    size_t players_data_size = event.get_winner().get_name().size();
    std::vector<int8_t> data(SEND_GAME_OVER_SIZE + players_data_size);
    size_t offset = 0;
    offset += encoder.encode_event_type(event.get_type(), &data[offset]);
    offset += encoder.encode_score(event.get_score(), &data[offset]);
    add_player_data(data, offset, event.get_winner());
    send(data.data(), data.size());
}

std::shared_ptr<Event> EventsProtocol::read_game_over() {
    std::vector<int8_t> data(READ_GAME_OVER_SIZE);
    read(data.data(), data.size());
    int score = encoder.decode_score(data);
    PlayerData winner = read_player_data();
    return std::make_shared<GameOver>(winner, score);
}

void EventsProtocol::add_game_room(const GameRoom &game_room, std::vector<int8_t> &data, size_t &offset) {
    offset += encoder.encode_game_code(game_room.get_game_code(), &data[offset]);
    offset += encoder.encode_actual_players(game_room.get_actual_players(), &data[offset]);
    offset += encoder.encode_max_players(game_room.get_max_players(), &data[offset]);
    add_name(game_room.get_game_name(), data, offset);
}

void EventsProtocol::add_name(const std::string &name, std::vector<int8_t> &data, size_t &offset) {
    offset += encoder.encode_len(name.size(), &data[offset]);
    if (name.empty()) {
        return;
    }
    offset += encoder.encode_string(name, &data[offset], name.size());
}

std::string EventsProtocol::read_name(size_t len) {
    if (len == 0) {
        return "";
    }
    std::vector<int8_t> name_data(len);
    read(name_data.data(), len);
    return encoder.decode_string(name_data, len);
}

GameRoom EventsProtocol::read_game_room() {
    std::vector<int8_t> data(GAME_ROOM_SIZE);
    read(data.data(), data.size());
    int game_code = encoder.decode_game_code(data);
    int actual_players = encoder.decode_actual_players(data);
    int max_players = encoder.decode_max_players(data);
    int len = encoder.decode_len(data);
    std::string game_name = read_name(len);
    return {game_code, game_name, actual_players, max_players};
}

void
EventsProtocol::add_players_data(std::vector<int8_t> &data, size_t &offset, const std::list<PlayerData> &players_data) {
    offset += encoder.encode_len(players_data.size(), &data[offset]);
    for (const auto &player_data: players_data) {
        add_player_data(data, offset, player_data);
    }
}

void EventsProtocol::add_player_data(std::vector<int8_t> &data, size_t &offset, const PlayerData &player_data) {
    offset += encoder.encode_player_id(player_data.get_id(), &data[offset]);
    add_name(player_data.get_name(), data, offset);
}

std::list<PlayerData> EventsProtocol::read_players_data() {
    std::vector<int8_t> data(LEN_SIZE);
    read(data.data(), data.size());
    int len = encoder.decode_len(data);

    std::list<PlayerData> players;
    for (int i = 0; i < len; i++) {
        players.emplace_back(read_player_data());
    }
    return players;
}

PlayerData EventsProtocol::read_player_data() {
    std::vector<int8_t> players_data(PLAYER_DATA_SIZE);
    read(players_data.data(), players_data.size());

    int id = encoder.decode_player_id(players_data);
    int name_len = encoder.decode_len(players_data);
    std::string name = read_name(name_len);
    PlayerData player = {id, name};
    return player;
}
