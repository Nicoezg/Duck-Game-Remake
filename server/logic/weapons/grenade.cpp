#include "grenade.h"
#include "server/logic/duck.h"

Grenade::Grenade(GameMap &map)
    : Weapon(map, 1, 5, WeaponId::GRENADE) {}

void Grenade::shoot(Duck *owner) {
    if (hasAmmo()) {
        createThrowable(owner,true);
        ammo--;
    }
}


