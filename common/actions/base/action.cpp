#include "action.h"
#include "common/actions/connection/create.h"

#include <iostream>

Action::Action(ActionType type) : type(type) {}

ActionType Action::get_type() const { return type; }

int Action::get_game_code() const {
  throw std::runtime_error("Action is not a game code action.");
}

std::string Action::get_player_name_1() const {
  throw std::runtime_error("Action is not a player name action.");
}

std::string Action::get_player_name_2() const {
  throw std::runtime_error("Action is not a player name action.");
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

bool Action::is_playing_dead() const {
  throw std::runtime_error("Action is not a play dead action.");
}

bool Action::is_jumping_flapping() const {
  throw std::runtime_error("Action is not a jump flap action.");
}

bool Action::is_aiming_upwards() const {
  throw std::runtime_error("Action is not an aim upwards action.");
}

bool Action::is_shooting() const {
  throw std::runtime_error("Action is not a shoot action.");
}

bool Action::is_picking_dropping() const {
  throw std::runtime_error("Action is not a pick drop action.");
}

int Action::get_max_players() const {
  throw std::runtime_error("Action is not a max players action.");
}

bool Action::is_still() const {
  throw std::runtime_error("Action is not a still action.");
}

std::string Action::get_game_name() const {
  throw std::runtime_error("Action is not a game name action.");
}

CheatId Action::get_cheat_id() const {
  throw std::runtime_error("Action is not a cheat action.");
}
