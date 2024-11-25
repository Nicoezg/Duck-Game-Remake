#include "grenade.h"
#include "server/logic/duck.h"
#include <iostream>

#define NAME GRENADE_NAME
const int AMMO = CONFIG.getBulletConfig(NAME).getAmmo();
const int REACH = CONFIG.getBulletConfig(NAME).getReach();
const int COOLDOWN = CONFIG.getBulletConfig(NAME).getCooldown();


Grenade::Grenade(GameMap &map)
    : Weapon(map, AMMO, REACH, WeaponId::GRENADE) {}

void Grenade::shoot(Duck *owner) {
    if (hasAmmo()) {
        createThrowable(map,owner,true);
        ammo--;
    }
}


