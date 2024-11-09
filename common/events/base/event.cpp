
#include "event.h"
#include "event_type.h"
#include "common/events/connection/game_join.h"
#include <stdexcept>

Event::Event(EventType type) : type(type) {}

EventType Event::get_type() { return type; }

int Event::get_game_code() const {
  throw std::runtime_error("Has no game code.");
}

bool Event::is_connected() const {
  throw std::runtime_error("Has no connection status.");
}

int Event::get_position_x() const {
  throw std::runtime_error("Has no x position.");
}

int Event::get_position_y() const {
  throw std::runtime_error("Has no y position.");
}

std::list<Player> Event::get_players() {
  throw std::runtime_error("Has no players.");
}

std::list<Bullet> Event::get_bullets() {
  throw std::runtime_error("Has no bullets.");
}

std::list<Crate> Event::get_crates() {
  throw std::runtime_error("Has no crates.");
}

std::list<Weapon> Event::get_weapons() {
  throw std::runtime_error("Has no weapons.");
}

int Event::get_player_id_1() const {
  throw std::runtime_error("Has no player id 1.");
}

int Event::get_player_id_2() const {
  throw std::runtime_error("Has no player id 2.");
}

int Event::get_max_players() const {
  throw std::runtime_error("Has no max players.");
}

int Event::get_actual_players() const {
  throw std::runtime_error("Has no actual players.");
}

std::list<GameRoom> Event::get_games() {
    throw std::runtime_error("Has no games.");
}
