#include "create.h"
#include "common/actions/base/action.h"

#include <iostream>

#include "common/actions/base/action_macros.h"
#include "common/events/connection/game_creation.h"

Create::Create(GameMode game_mode, int max_players)
    : Action(CREATE_REQUEST), game_mode(game_mode), max_players(max_players) {}

GameMode Create::get_game_mode() const { return game_mode; }

int Create::get_max_players() const {
    return max_players;
}
