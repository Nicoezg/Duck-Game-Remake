//
// Created by fran on 20/11/24.
//

#include "no_weapon.h"

NoWeapon::NoWeapon(GameMap &map) : Weapon(map, 0, 0, WeaponId::NO_WEAPON) {}

bool NoWeapon::isReadyToShoot() const { return false; }

void NoWeapon::shoot(Duck *) {}

void NoWeapon::replenishAmmo() {}
