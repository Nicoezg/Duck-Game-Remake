//
// Created by fran on 21/10/24.
//

#include <stdexcept>
#include "game_join.h"
#include "event_type.h"

GameJoin::GameJoin(int player_id_1, int player_id_2, bool connected) : Event(JOIN_GAME),
    player_id_1(player_id_1), player_id_2(player_id_2), connected(connected) {}

int GameJoin::get_player_id_1() const {
    return player_id_1;
}

int GameJoin::get_player_id_2() const {
    return player_id_2;
}

int GameJoin::get_game_code() const {
    throw std::runtime_error("GameJoin has no game code");
}

bool GameJoin::is_connected() const {
    return connected;
}

