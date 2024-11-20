#include "sniper.h"

#define AMMO CONFIG.getSniperAmmo()
#define REACH CONFIG.getSniperReach()
#define COOLDDOWN CONFIG.getSniperCooldown()

Sniper::Sniper(GameMap &map) : Weapon(map, AMMO, REACH, WeaponId::SNIPER) {}

void Sniper::shoot(Duck *owner) {
  if (hasAmmo()) {
    createBullet(owner, 0, true, reach, BulletId::SHOT);
      increaseCooldown(COOLDDOWN);
    ammo--;
  }
}

