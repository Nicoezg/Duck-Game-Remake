#include "weapon.h"


Weapon::Weapon(WeaponId weapon_id, int position_x, int position_y)
    : weapon_id(weapon_id), position_x(position_x), position_y(position_y) {}

WeaponId Weapon::get_weapon_id() const { return weapon_id; }

int Weapon::get_position_x() const { return position_x; }

int Weapon::get_position_y() const { return position_y; }
