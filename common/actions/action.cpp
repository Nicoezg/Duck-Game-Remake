#include "action.h"

#include <iostream>

Action::Action(std::string name, ActionType type, int player_id, GameMode game_mode)
    : name(std::move(name)), type(type), player_id(player_id), game_mode(game_mode) {}

std::string Action::get_name() const { return name; }

int Action::get_player_id() const { return player_id; }

ActionType Action::get_type() const { return type; }

GameMode Action::get_game_mode() const { return game_mode; }

int Action::get_game_code() const {
    throw std::runtime_error("Move is not a game code action.");
}
