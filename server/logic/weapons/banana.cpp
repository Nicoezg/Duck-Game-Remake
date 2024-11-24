#include "banana.h"

Banana::Banana(GameMap &map)
    : Weapon(map, 1, 100, WeaponId::BANANA) {}

void Banana::shoot(Duck *owner) {
    if (hasAmmo()) {
        createThrowable(map,owner,false);
    }
}