//
// Created by fran on 21/10/24.
//

#include <stdexcept>
#include "join.h"


Join::Join(int& game_code) : Action("UNIRSE", JOIN_REQUEST, 0), game_code(game_code) {}

int Join::get_game_code() const {
    return game_code;
}

bool Join::is_x_direction() const {
    throw std::runtime_error("Join is not a direction action.");
}

bool Join::is_y_direction() const {
    throw std::runtime_error("Join is not a direction action.");
}


