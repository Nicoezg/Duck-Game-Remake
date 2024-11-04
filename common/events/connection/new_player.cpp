//
// Created by fran on 04/11/24.
//

#include "new_player.h"

NewPlayer::NewPlayer(int max_players, int actual_players)
    : Event(NEW_PLAYER), max_players(max_players), actual_players(actual_players) {}

int NewPlayer::get_max_players() const {
    return max_players;
}

int NewPlayer::get_actual_players() const {
    return actual_players;
}
