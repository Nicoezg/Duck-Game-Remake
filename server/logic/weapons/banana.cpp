#include "banana.h"

#define NAME BANANA_NAME
const int AMMO = CONFIG.getBulletConfig(NAME).getAmmo();
const int REACH = CONFIG.getBulletConfig(NAME).getReach();
const int COOLDOWN = CONFIG.getBulletConfig(NAME).getCooldown();

Banana::Banana(GameMap &map)
    : Weapon(map, 1, 100, WeaponId::BANANA) {}

void Banana::shoot(Duck *owner) {
    if (hasAmmo()) {
        createThrowable(map,owner,false);
    }
}

void Banana::replenishAmmo(){
  ammo = AMMO;
}