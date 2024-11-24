//
// Created by fran on 04/11/24.
//

#include "refresh_games.h"

Refresh::Refresh(std::list<GameRoom> games) : Event(REFRESH_GAMES), games(std::move(games)) {}

std::list<GameRoom> Refresh::get_games() const {
    return games;
}

bool Refresh::is_connected() const {
    return false;
}
