#include "ak47.h"
#include "server/logic/duck.h"
#define NAME AK47_NAME
const int AMMO = CONFIG.getBulletConfig(NAME).getAmmo();
const int REACH = CONFIG.getBulletConfig(NAME).getReach();
const int COOLDOWN = CONFIG.getBulletConfig(NAME).getCooldown();

Ak47::Ak47(GameMap &map) : Weapon(map, AMMO, REACH, WeaponId::AK47) {}

void Ak47::shoot(Duck *owner) {
  if (hasAmmo()) {
    createBullet(owner, 0, false, REACH, BulletId::SHOT);
    increaseCooldown(COOLDOWN);
    owner->standBack(7);
    ammo--;
  }
}