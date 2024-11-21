#include "magnum.h"
#include "server/logic/duck.h"

#define NAME MAGNUM_NAME
const int AMMO = CONFIG.getBulletConfig(NAME).getAmmo();
const int REACH = CONFIG.getBulletConfig(NAME).getReach();
const int COOLDOWN = CONFIG.getBulletConfig(NAME).getCooldown();

Magnum::Magnum(GameMap &map) : Weapon(map, AMMO, REACH, WeaponId::MAGNUM) {}

void Magnum::shoot(Duck *owner) {
  if (hasAmmo() && isReadyToShoot()) {
    createBullet(owner, 2, false, reach, BulletId::SHOT);
    increaseCooldown(10);
    owner->standBack(5);
    ammo--;
  }
  
}
