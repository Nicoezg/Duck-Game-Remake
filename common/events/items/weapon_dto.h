#ifndef TALLER_TP_WEAPON_DTO_H
#define TALLER_TP_WEAPON_DTO_H

#include "weapon_macros.h"
#include <string>

class WeaponDTO {
private:
  WeaponId weapon_id;
  int position_x;
  int position_y;
  bool shooting;
  bool hasAmmo;

public:
  explicit WeaponDTO(WeaponId weapon_id = NO_WEAPON, int position_x = 0,
                     int position_y = 0, bool shooting = false,
                     bool hasAmmo = false);

  WeaponId get_id() const;

  bool is_shooting() const;

  int get_position_x() const;

  int get_position_y() const;

  bool has_ammo() const;
};

#endif // TALLER_TP_WEAPON_DTO_H
