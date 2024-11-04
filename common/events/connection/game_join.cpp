//
// Created by fran on 21/10/24.
//

#include "game_join.h"
#include "common/events/base/event_type.h"
#include <stdexcept>

GameJoin::GameJoin(int player_id_1, int player_id_2, bool connected, int actual, int max)
    : Event(JOIN_GAME), player_id_1(player_id_1), player_id_2(player_id_2),
      connected(connected), actual_players(actual), max_players(max) {}

int GameJoin::get_player_id_1() const { return player_id_1; }

int GameJoin::get_player_id_2() const { return player_id_2; }

int GameJoin::get_game_code() const {
  throw std::runtime_error("GameJoin has no game code");
}

bool GameJoin::is_connected() const { return connected; }

int GameJoin::get_max_players() const {
    return max_players;
}

int GameJoin::get_actual_players() const {
    return actual_players;
}