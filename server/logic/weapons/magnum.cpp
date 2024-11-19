#include "magnum.h"
#include "server/logic/duck.h"

#define AMMO CONFIG.getMagnumAmmo()
#define REACH CONFIG.getMagnumReach()

Magnum::Magnum(GameMap &map) : Weapon(map, AMMO, REACH, WeaponId::MAGNUM) {}

void Magnum::shoot(Duck *owner) {
  if (hasAmmo()) {
    createBullet(owner, 2, false, reach, BulletId::SHOT);
    owner->standBack(5);
    ammo--;
  }
  
}
