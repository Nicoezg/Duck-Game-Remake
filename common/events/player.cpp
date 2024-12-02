//
// Created by fran on 24/10/24.
//

#include "player.h"
#include "player_macros.h"
#include <sstream>

PlayerDTO::PlayerDTO(int player_id, int position_x, int position_y, bool right,
                     State state, WeaponDTO weapon, HelmetDTO helmet,
                     Chestplate chestplate)
    : player_id(player_id), position_x(position_x), position_y(position_y),
      right(right), state(state), weapon(weapon), helmet(helmet),
      chestplate(chestplate) {}

int PlayerDTO::get_player_id() const { return player_id; }

int PlayerDTO::get_position_x() const { return position_x; }

int PlayerDTO::get_position_y() const { return position_y; }

bool PlayerDTO::is_right() const { return right; }

State PlayerDTO::get_state() const { return state; }

WeaponDTO PlayerDTO::get_weapon() const { return weapon; }

HelmetDTO PlayerDTO::get_helmet() const { return helmet; }

Chestplate PlayerDTO::get_chestplate() const { return chestplate; }
