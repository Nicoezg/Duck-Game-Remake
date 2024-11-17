//
// Created by fran on 24/10/24.
//

#ifndef TALLER_TP_PLAYER_H
#define TALLER_TP_PLAYER_H

#include "items/chestplate.h"
#include "items/helmet.h"
#include "common/events/items/weapon_dto.h"
#include "player_macros.h"
#include <string>

class PlayerDTO {
private:
  int player_id;
  int position_x;
  int position_y;
  bool right;
  enum State state;
  WeaponDTO weapon;
  HelmetDTO helmet;
  Chestplate chestplate;

public:
  PlayerDTO(int player_id, int position_x, int position_y, bool right, State state,
            WeaponDTO weapon, HelmetDTO helmet, Chestplate chestplate);

  int get_player_id() const;

  int get_position_x() const;

  int get_position_y() const;

  bool is_right() const;

  State get_state() const;

    WeaponDTO get_weapon() const;

  HelmetDTO get_helmet() const;

  Chestplate get_chestplate() const;
};

#endif // TALLER_TP_PLAYER_H