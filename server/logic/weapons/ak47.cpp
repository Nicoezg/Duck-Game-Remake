#include "ak47.h"
#include "server/logic/duck.h"
#include <iostream>

#define NAME AK47_NAME
const int AMMO = CONFIG.getBulletConfig(NAME).getAmmo();
const int REACH = CONFIG.getBulletConfig(NAME).getReach();
const int COOLDOWN = CONFIG.getBulletConfig(NAME).getCooldown();
const int RECOIL_X = 7;
const int RECOIL_Y = 8;
const int MAX_RECOIL_Y = 75;

Ak47::Ak47(GameMap &map)
    : Weapon(map, AMMO, REACH, WeaponId::AK47), consecutiveShots(0) {}

void Ak47::shoot(Duck *owner) {
  if (hasAmmo()) {
    createBullet(owner, consecutiveShots, false, REACH, BulletId::SHOT);
    increaseCooldown(COOLDOWN);
    owner->standBack(RECOIL_X);
    ammo--;
  }
}

void Ak47::replenishAmmo() {
  ammo = AMMO;
  consecutiveShots = 0;
}

void Ak47::resetConsecutiveShots() {
  if (consecutiveShots > 0) {
    consecutiveShots--;
  }
}

void Ak47::increaseConsecutiveShots() {
  if (consecutiveShots + RECOIL_Y < MAX_RECOIL_Y) {
    consecutiveShots += RECOIL_Y;
  }
}