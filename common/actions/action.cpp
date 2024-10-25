#include "action.h"
#include "create.h"

#include <iostream>

Action::Action(ActionType type) : type(type) {}

ActionType Action::get_type() const { return type; }

int Action::get_game_code() const {
    throw std::runtime_error("Action is not a game code action.");
}

int Action::get_player_id() const {
    throw std::runtime_error("Action is not a player id action.");
}

GameMode Action::get_game_mode() const {
    throw std::runtime_error("Action is not a game mode action.");
}

bool Action::is_right() const {
    throw std::runtime_error("Action is not a right action.");
}
