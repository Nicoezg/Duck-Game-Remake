#include "sniper.h"

Sniper::Sniper(GameMap &map) : Weapon(map, 100, 64, WeaponId::SNIPER) {}

void Sniper::shoot(Duck *owner) {
  if (hasAmmo()) {
    createBullet(owner, 10, true, reach, BulletId::SHOT);
    ammo--;
  }
}
