#include "weapon_dto.h"


WeaponDTO::WeaponDTO(WeaponId weapon_id, int position_x, int position_y, bool shooting, bool hasAmmo)
    : weapon_id(weapon_id), position_x(position_x), position_y(position_y), shooting(shooting), hasAmmo(hasAmmo) {}


WeaponId WeaponDTO::get_id() const { return weapon_id; }

bool WeaponDTO::is_shooting() const { return shooting; }

int WeaponDTO::get_position_x() const { return position_x; }

int WeaponDTO::get_position_y() const { return position_y; }

bool WeaponDTO::has_ammo() const {return hasAmmo; }
