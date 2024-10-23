#include "create.h"

#include <iostream>

#include "action_macros.h"
#include "common/events/game_creation.h"


Create::Create() : Action("CONECTAR", CREATE_REQUEST, 0){}


int Create::get_game_code() const {
    throw std::runtime_error("Create is not a game code action.");
}

bool Create::is_x_direction() const {
    throw std::runtime_error("Create is not a direction action.");
}

bool Create::is_y_direction() const {
    throw std::runtime_error("Create is not a direction action.");
}
