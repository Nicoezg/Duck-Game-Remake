#include "duelos.h"
#include "server/logic/duck.h"
#include <cstdlib>

Duelos::Duelos(GameMap &map) : Weapon(map, 1, 5, WeaponId::DUEL_PISTOL) {}

void Duelos::shoot(Duck *shooter) {
  if (hasAmmo()) {
    createBullet(shooter, 10, true, reach, BulletId::SHOT);
    ammo--;
  }
}
