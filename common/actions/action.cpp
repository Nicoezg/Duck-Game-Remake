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
