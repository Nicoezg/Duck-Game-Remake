#include "grenade.h"
#include "server/logic/duck.h"

Grenade::Grenade(GameMap &map)
    : Weapon(map, 1, 5, WeaponId::GRENADE), isArmed(false), framesToExplode(0) {}

void Grenade::shoot(Duck *owner) {

}


