//
// Created by fran on 21/10/24.
//

#include <stdexcept>
#include "game_join.h"
#include "event_type.h"

GameJoin::GameJoin(int player_id, bool connected) : Event(JOIN_GAME), player_id(player_id), connected(connected) {}

int GameJoin::get_player_id() const {
    return player_id;
}

int GameJoin::get_game_code() const {
    throw std::runtime_error("GameJoin has no game code");
}

bool GameJoin::is_connected() const {
    return connected;
}

