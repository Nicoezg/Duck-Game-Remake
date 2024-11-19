#ifndef TALLER_TP_WEAPON_DTO_H
#define TALLER_TP_WEAPON_DTO_H

#include <string>
#include "weapon_macros.h"


class WeaponDTO {
private:
    WeaponId weapon_id;
    int position_x;
    int position_y;
    bool shooting;

public:
    WeaponDTO(WeaponId weapon_id = NO_WEAPON, int position_x = 0, int position_y = 0, bool shooting = false);
    
    WeaponId get_id() const;

    bool is_shooting() const;

    int get_position_x() const;

    int get_position_y() const;
};

#endif // TALLER_TP_WEAPON_DTO_H
