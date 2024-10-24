#include "create.h"

#include <iostream>

#include "action_macros.h"
#include "common/events/game_creation.h"


Create::Create(GameMode game_mode) : Action("CONECTAR", CREATE_REQUEST, 0, game_mode){}


bool Create::is_x_direction() const {
    throw std::runtime_error("Create is not a direction action.");
}

bool Create::is_y_direction() const {
    throw std::runtime_error("Create is not a direction action.");
}
