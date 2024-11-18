#include "magnum.h"
#include "server/logic/duck.h"

Magnum::Magnum(GameMap &map) : Weapon(map, 100, 20, WeaponId::MAGNUM) {}

void Magnum::shoot(Duck *owner) {
  createBullet(owner, 2, false, reach, BulletId::SHOT);
  if (hasAmmo()) {
    owner->standBack(2);
  }
}
