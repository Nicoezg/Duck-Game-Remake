#include "create.h"
#include "action.h"

#include <iostream>

#include "action_macros.h"
#include "common/events/game_creation.h"

Create::Create(GameMode game_mode)
    : Action(CREATE_REQUEST), game_mode(game_mode) {}

GameMode Create::get_game_mode() const { return game_mode; }
