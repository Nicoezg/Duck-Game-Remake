#include "shotgun.h"

#define NAME SHOTGUN_NAME
const int AMMO = CONFIG.getBulletConfig(NAME).getAmmo();
const int REACH = CONFIG.getBulletConfig(NAME).getReach();
const int COOLDOWN = CONFIG.getBulletConfig(NAME).getCooldown();

Shotgun::Shotgun(GameMap &map) : Weapon(map, AMMO, REACH, WeaponId::SHOTGUN) {}

void Shotgun::shoot(Duck *owner) {
  if (hasAmmo()) {
    int angles[6] = {0, 10, -10, 20, -20, 15};
    for (int angle : angles) {
      createBullet(owner, angle, false, reach, BulletId::SHOT);
    }
    ammo--;

    lastShotTime = 0;
  }
}

void Shotgun::replenishAmmo(){
  ammo = AMMO;
}