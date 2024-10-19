#include "common/protocol/action.h"

#include <cstdint>
#include <iostream>
#include <sstream>
#include <utility>

#include "common/protocol/action_macros.h"

Action::Action(uint16_t id, std::string name)
    : id(id), name(std::move(name)), game_code(){}

Action::Action()
    : id(0), name(), game_code() {}

Action::Action(std::string name)
    : id(0), name(std::move(name)), game_code(){}

std::string Action::get_name() const { return name; }


std::string Action::print_game_code() const {
  std::stringstream ss;
  ss << "Codigo de juego: " << game_code << std::endl;
  return ss.str();
}

uint32_t Action::get_game_code() const { return game_code; }

bool Action::is_attack() const { return name == ACTION_ATTACK; }

bool Action::is_broadcast() const { return name == ACTION_BROADCAST; }

bool Action::is_connect() const {
  return name == ACTION_CREATE || name == ACTION_JOIN;
}

std::string Action::get_text() const {
    std::stringstream ss;
    ss
    << "Accion: " << name << std::endl
    << "ID: " << id << std::endl
    << "Codigo de juego: " << game_code << std::endl;
    return ss.str();
}