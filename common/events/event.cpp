
#include "event_type.h"
#include "game_join.h"
#include <stdexcept>
#include "event.h"

Event::Event(EventType type) : type(type) {}

EventType Event::get_type() {
    return type;
}

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
