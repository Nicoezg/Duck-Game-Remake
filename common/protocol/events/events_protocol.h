#ifndef TALLER_TP_EVENTS_PROTOCOL_H
#define TALLER_TP_EVENTS_PROTOCOL_H

#include "common/events/base/event.h"
#include "common/protocol/common/protocol.h"

#define EVENT_TYPE_SIZE sizeof(int8_t)
#define PLAYERS_DATA_ID_SIZE sizeof(uint16_t)
#define GAME_CODE_SIZE sizeof(uint32_t)
#define CONNECTED_SIZE sizeof(uint8_t)
#define MAX_PLAYER_SIZE sizeof(uint8_t)
#define ACTUAL_PLAYER_SIZE sizeof(uint8_t)
#define COORDINATE_SIZE sizeof(int16_t)
#define LEN_SIZE sizeof(uint8_t)
#define PLAYER_COORDINATE sizeof(int16_t)
#define PLAYER_IS_RIGHT_SIZE sizeof(uint8_t)
#define PLAYER_STATE_SIZE sizeof(uint8_t)
#define HEALTH_SIZE sizeof(uint8_t)
#define CHESTPLATE_SIZE sizeof(uint8_t)
#define ANGLE_SIZE sizeof(uint16_t)

#define IS_SHOOTING_SIZE sizeof(uint8_t)
#define WEAPON_ID_SIZE sizeof(uint8_t)

#define BULLET_ID_SIZE sizeof(uint8_t)
#define BULLET_IS_RIGHT_SIZE sizeof(uint8_t)

#define THROWABLE_ID_SIZE sizeof(uint8_t)

#define BACKGROUND_ID_SIZE sizeof(uint8_t)
#define TILE_ID_SIZE sizeof(uint8_t)
#define SCORE_SIZE sizeof(uint16_t)


#define WEAPONS_SIZE (WEAPON_ID_SIZE + COORDINATE_SIZE * 2 + IS_SHOOTING_SIZE)

#define PLAYER_DATA_SIZE (PLAYERS_DATA_ID_SIZE + LEN_SIZE)
#define GAME_ROOM_SIZE (MAX_PLAYER_SIZE + ACTUAL_PLAYER_SIZE + GAME_CODE_SIZE + LEN_SIZE)

#define READ_NEW_PLAYER_SIZE (ACTUAL_PLAYER_SIZE + MAX_PLAYER_SIZE)

#define READ_CREATE_GAME_SIZE (2 * PLAYERS_DATA_ID_SIZE)
#define READ_JOIN_GAME_SIZE (2 * PLAYERS_DATA_ID_SIZE + CONNECTED_SIZE)

#define READ_BULLET_SIZE (COORDINATE_SIZE * 2 + BULLET_ID_SIZE + ANGLE_SIZE + BULLET_IS_RIGHT_SIZE)
#define SEND_BULLET_SIZE READ_BULLET_SIZE

#define READ_CRATE_SIZE (COORDINATE_SIZE * 2 + sizeof(uint8_t) * 2)
#define SEND_CRATE_SIZE READ_CRATE_SIZE

#define READ_ITEM_SPAWN_SIZE (COORDINATE_SIZE * 2 + sizeof(uint8_t))
#define SEND_ITEM_SPAWN_SIZE READ_ITEM_SPAWN_SIZE

#define READ_EXPLOSION_SIZE (COORDINATE_SIZE * 2 + sizeof(uint8_t))
#define SEND_EXPLOSION_SIZE READ_EXPLOSION_SIZE

#define READ_THROWABLE_SIZE (COORDINATE_SIZE * 2 + THROWABLE_ID_SIZE + sizeof(uint8_t) + ANGLE_SIZE + sizeof(uint8_t))
#define SEND_THROWABLE_SIZE READ_THROWABLE_SIZE

#define READ_PLAYER_SIZE                                                       \
  (2 * PLAYER_COORDINATE + PLAYERS_DATA_ID_SIZE + PLAYER_STATE_SIZE +               \
   PLAYER_IS_RIGHT_SIZE + WEAPONS_SIZE + HEALTH_SIZE + CHESTPLATE_SIZE)

#define READ_TILE_SIZE (COORDINATE_SIZE * 3 + TILE_ID_SIZE)

#define READ_BACKGROUND_SIZE (COORDINATE_SIZE * 2 + BACKGROUND_ID_SIZE)
#define SEND_BACKGROUND_SIZE READ_BACKGROUND_SIZE

#define SEND_CREATE_GAME_SIZE (READ_CREATE_GAME_SIZE + EVENT_TYPE_SIZE)
#define SEND_JOIN_GAME_SIZE (READ_JOIN_GAME_SIZE + EVENT_TYPE_SIZE)

#define SEND_PLAYER_SIZE READ_PLAYER_SIZE

#define SEND_TILE_SIZE READ_TILE_SIZE

#define SEND_NEW_PLAYER_SIZE (READ_NEW_PLAYER_SIZE + EVENT_TYPE_SIZE)

#define READ_GAME_OVER_SIZE (SCORE_SIZE)
#define SEND_GAME_OVER_SIZE (READ_GAME_OVER_SIZE + PLAYER_DATA_SIZE + EVENT_TYPE_SIZE)

#define SEND_SCORE_SIZE (EVENT_TYPE_SIZE)


class EventsProtocol : public Protocol {
private:
    Encoder encoder;

    void send_create(const Event &event);

    void send_join(const Event &event);

    std::shared_ptr<Event> read_create();

    std::shared_ptr<Event> read_join();

public:
    EventsProtocol(Socket *socket, Encoder encoder);

    void send_element(Event &event);

    std::shared_ptr<Event> read_element();

    EventType read_event_type();

    std::shared_ptr<Event> read_broadcast();

    void send_broadcast(const Event &event);

    void send_refresh(const Event &event);

    std::shared_ptr<Event> read_refresh_game();

    std::shared_ptr<Event> read_new_player();

    void send_new_player(const Event &event);

    void send_start_game(const Event &event);

    WeaponDTO read_weapon(std::vector<int8_t> &data);

    HelmetDTO read_helmet(std::vector<int8_t> &data);

    Chestplate read_chestplate(std::vector<int8_t> &data);

    void add_chestplate(std::vector<int8_t> &data, Chestplate chestplate, size_t &offset);

    void add_health(std::vector<int8_t> &data, HelmetDTO helmet, size_t &offset);

    void add_weapon(std::vector<int8_t> &data, WeaponDTO weapon, size_t &offset);

    void add_players(const Event &event, std::vector<int8_t> &data, size_t &offset);

    void send_map(const Event &event);

    std::shared_ptr<Event> read_map();

    void add_platforms(const Event &event, std::vector<int8_t> &data, size_t &offset);

    void add_bullets(const Event &event, std::vector<int8_t> &data, size_t &offset);

    void add_crates(const Event&, std::vector<int8_t> &data, size_t &offset);

    void add_item_spawns(const Event&, std::vector<int8_t> &data, size_t &offset);

    void add_explosions(const Event&, std::vector<int8_t> &data, size_t &offset);

    void add_throwables(const Event&, std::vector<int8_t> &data, size_t &offset);

    void send_game_over(const Event &event);

    std::shared_ptr<Event> read_game_over();

    void add_game_room(const GameRoom &game_room, std::vector<int8_t> &data, size_t &offset);

    void add_name(const std::string &name, std::vector<int8_t> &data, size_t &offset);

    GameRoom read_game_room();

    void add_players_data(std::vector<int8_t> &data, size_t &offset, const std::list<PlayerData> &players_data);

    std::list<PlayerData> read_players_data();

    size_t get_size_to_send(const Event &event, size_t start);

    std::string read_name(size_t len);

    void add_player_data(std::vector<int8_t> &data, size_t &offset, const PlayerData &player_data);

    PlayerData read_player_data();

    Tile read_tile(std::vector<int8_t> &data);

    std::list<std::string> read_names();

    std::list<int> read_scores();

    std::shared_ptr<Event> read_score();

    void add_scores(std::vector<int8_t> &data, size_t &offset, const std::list<int> &scores);

    void add_names(std::vector<int8_t> &data, size_t &offset, const std::list<std::string> &names);

    void send_score(const Event &event);
};

#endif // TALLER_TP_EVENTS_PROTOCOL_H
