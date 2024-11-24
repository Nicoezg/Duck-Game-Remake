//
// Created by fran on 21/10/24.
//

#include "game_join.h"
#include "common/events/base/event_type.h"
#include <stdexcept>
#include <utility>

GameJoin::GameJoin(int player_id_1, int player_id_2, bool connected, GameRoom game_room,
                   std::list<PlayerData> players_data)
    : Event(JOIN_GAME), player_id_1(player_id_1), player_id_2(player_id_2),
      connected(connected), game_room(std::move(game_room)), players_data(std::move(players_data)) {}

int GameJoin::get_player_id_1() const { return player_id_1; }

int GameJoin::get_player_id_2() const { return player_id_2; }

std::list<PlayerData> GameJoin::get_players_data() const {
    return players_data;
}

bool GameJoin::is_connected() const { return connected; }

GameRoom GameJoin::get_game_room() const { return game_room; }