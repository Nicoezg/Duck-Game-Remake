//
// Created by fran on 13/11/24.
//

#include "weapon.h"

Weapon::Weapon(int ammo, int reach) : reach(reach), ammo(ammo), reloading(false), lastShot(0) {}
