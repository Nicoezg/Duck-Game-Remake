//
// Created by fran on 24/10/24.
//

#include <sstream>
#include "player.h"

Player::Player(int player_id, int position_x, int position_y) : player_id(player_id),
    position_x(position_x), position_y(position_y) {}

int Player::get_player_id() const {
    return player_id;
}

int Player::get_position_x() const {
    return position_x;
}

std::string Player::get_text() const {
    std::stringstream ss;
    ss << "PlayerId: " << player_id << " Position: (" << position_x << ", " << position_y << ")";
    return ss.str();
}

int Player::get_position_y() const {
    return position_y;
}

void Player::move(bool is_right) {
    if (is_right) {
        position_x++;
    } else {
        position_x--;
    }
}
