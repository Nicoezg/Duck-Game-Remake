#include "duelos.h"
#include "server/logic/duck.h"
#include <cstdlib>

#define NAME DUELOS_NAME
const int AMMO = CONFIG.getBulletConfig(NAME).getAmmo();
const int REACH = CONFIG.getBulletConfig(NAME).getReach();
const int COOLDOWN = CONFIG.getBulletConfig(NAME).getCooldown();

Duelos::Duelos(GameMap &map) : Weapon(map, AMMO, REACH, WeaponId::DUEL_PISTOL) {}

void Duelos::shoot(Duck *shooter) {
  if (hasAmmo()) {
    createBullet(shooter, -10, true, reach, BulletId::SHOT);
    ammo--;
  }
}

void Duelos::replenishAmmo(){
  ammo = AMMO;
}
