#include "magnum.h"
#include "server/logic/duck.h"
#include <iostream>

#define NAME MAGNUM_NAME
const int AMMO = CONFIG.getBulletConfig(NAME).getAmmo();
const int REACH = CONFIG.getBulletConfig(NAME).getReach();
const int COOLDOWN = CONFIG.getBulletConfig(NAME).getCooldown();
const int RECOIL_X = 5;
const int RECOIL_Y = 15;
const int MAX_RECOIL_Y = 65;

Magnum::Magnum(GameMap &map)
    : Weapon(map, AMMO, REACH, WeaponId::MAGNUM), consecutiveShots(0) {}

void Magnum::shoot(Duck *owner) {
  if (hasAmmo() && isReadyToShoot()) {
    createBullet(owner, consecutiveShots, false, reach, BulletId::SHOT);
    increaseCooldown(COOLDOWN);
    owner->standBack(RECOIL_X);
    ammo--;
  }
}

void Magnum::replenishAmmo() { ammo = AMMO; }

void Magnum::resetConsecutiveShots() {
  if (consecutiveShots > 0) {
    consecutiveShots--;
  }
}

void Magnum::increaseConsecutiveShots() {
  if (consecutiveShots + RECOIL_Y < MAX_RECOIL_Y) {
    consecutiveShots += RECOIL_Y;
  }
}
