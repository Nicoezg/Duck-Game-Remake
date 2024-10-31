//
// Created by fran on 24/10/24.
//

#include "player.h"
#include <sstream>

Player::Player(int player_id, int position_x, int position_y, bool dead, bool jumping, bool falling, bool playing_dead, bool right, bool aiming_upwards, bool new_movement)
    : player_id(player_id), position_x(position_x), position_y(position_y), dead(), jumping(), falling(), playing_dead(), right(), aiming_upwards(), new_movement() {}

int Player::get_player_id() const { return player_id; }

int Player::get_position_x() const { return position_x; }

std::string Player::get_text() const {
  std::stringstream ss;
  ss << "PlayerId: " << player_id << " Position: (" << position_x << ", "
     << position_y << ")";
  return ss.str();
}

int Player::get_position_y() const { return position_y; }

void Player::move(bool is_right) {
  if (is_right) {
    position_x++;
  } else {
    position_x--;
  }
}

bool Player::is_dead() const { return dead; }

bool Player::is_jumping() const { return jumping; }

bool Player::is_falling() const { return falling; }

bool Player::is_playing_dead() const { return playing_dead; }

bool Player::is_right() const { return right; }

bool Player::is_aiming_upwards() const { return aiming_upwards; }

bool Player::is_new_movement() const { return new_movement; }
