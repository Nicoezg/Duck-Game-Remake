#ifndef TALLER_TP_WEAPON_H
#define TALLER_TP_WEAPON_H

#include <string>
#include "weapon_macros.h"



class Weapon {
private:
  WeaponId weapon_id;
  int position_x;
  int position_y;

public:
  Weapon(WeaponId weapon_id = NO_WEAPON, int position_x = 0, int position_y = 0);

  WeaponId get_weapon_id() const;

  int get_position_x() const;

  int get_position_y() const;
};

#endif // TALLER_TP_WEAPON_H
