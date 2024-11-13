
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

std::list<PlayerDTO> Event::get_players() const {
    throw std::runtime_error("Has no players.");
}

std::list<BulletDTO> Event::get_bullets() const {
    throw std::runtime_error("Has no bullets.");
}

std::list<CrateDTO> Event::get_crates() const {
    throw std::runtime_error("Has no crates.");
}

std::list<WeaponDTO> Event::get_weapons() const {
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

std::vector<Tile> Event::get_platforms() const {
    throw std::runtime_error("Has no platforms.");
}

int Event::get_background_id() const {
    throw std::runtime_error("Has no background id.");
}

int Event::get_width() const {
    throw std::runtime_error("Has no width.");
}

int Event::get_length() const {
    throw std::runtime_error("Has no length.");
}

std::vector<std::string> Event::get_names() const {
    throw std::runtime_error("Has no names.");
}

std::vector<int> Event::get_scores() const {
    throw std::runtime_error("Has no scores.");
}

std::string Event::get_winner() const {
    throw std::runtime_error("Has no winner.");
}

int Event::get_score() const {
    throw std::runtime_error("Has no score.");
}
