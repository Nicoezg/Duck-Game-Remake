//
// Created by fran on 21/10/24.
//

#include "join.h"
#include "common/actions/base/action.h"
#include "create.h"
#include <iostream>
#include <stdexcept>

Join::Join(int &game_code, GameMode game_mode)
    : Action(JOIN_REQUEST), game_code(game_code), game_mode(game_mode) {}

int Join::get_game_code() const { return game_code; }

GameMode Join::get_game_mode() const { return game_mode; }
