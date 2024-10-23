#include "action.h"

#include <iostream>

Action::Action(std::string name, ActionType type, int player_id)
    : name(std::move(name)), type(type), player_id(player_id) {}

std::string Action::get_name() const { return name; }

int Action::get_player_id() const { return player_id; }

ActionType Action::get_type() const { return type; }
