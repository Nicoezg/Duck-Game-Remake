#include "pewpewlaser.h"
#include <iostream>

#define NAME PEW_PEW_LASER_NAME
const int AMMO = CONFIG.getBulletConfig(NAME).getAmmo();
const int REACH = CONFIG.getBulletConfig(NAME).getReach();
const int COOLDOWN = CONFIG.getBulletConfig(NAME).getCooldown();


PewPewLaser::PewPewLaser(GameMap &map)
    : Weapon(map, AMMO, REACH,
             WeaponId::PEW_PEW_LASER) {}

void PewPewLaser::shoot(Duck *owner) {

    if (hasAmmo()) {
      int angles[3] = {0, 20, -20};
      for (int angle : angles) {
          createBullet(owner, angle, false, reach, BulletId::LASER_REBOUND);
      }
      ammo--;

      lastShotTime = 0;
    }
}
