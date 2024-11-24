//
// Created by fran on 24/11/24.
//

#include "player_data.h"

PlayerData::PlayerData(int id, std::string name) : id(id), name(std::move(name)) {}

int PlayerData::get_id() const {
    return id;
}

std::string PlayerData::get_name() const {
    return name;
}
