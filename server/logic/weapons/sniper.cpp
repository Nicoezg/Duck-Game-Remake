#include "sniper.h"

#define NAME SNIPER_NAME
const int AMMO = CONFIG.getBulletConfig(NAME).getAmmo();
const int REACH = CONFIG.getBulletConfig(NAME).getReach();
const int COOLDOWN = CONFIG.getBulletConfig(NAME).getCooldown();

Sniper::Sniper(GameMap &map) : Weapon(map, AMMO, REACH, WeaponId::SNIPER) {}

void Sniper::shoot(Duck *owner) {
  if (hasAmmo()) {
    createBullet(owner, 0, true, reach, BulletId::SHOT);
    increaseCooldown(COOLDOWN);
    ammo--;
  }
}

void Sniper::replenishAmmo(){
  ammo = AMMO;
}

