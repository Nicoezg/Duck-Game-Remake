#include "pewpewlaser.h"
#include <iostream>

PewPewLaser::PewPewLaser(GameMap &map)
    : Weapon(map, CONFIG.getPewPewLaserAmmo(), CONFIG.getPewPewLaserReach(),
             WeaponId::PEW_PEW_LASER) {}

void PewPewLaser::shoot(Duck *owner) {

    if (hasAmmo()) {
      int angles[3] = {0, 10, -10};
      for (int angle : angles) {
          createBullet(owner, angle, false, reach, BulletId::LASER_REBOUND);
      }
      ammo--;

      lastShotTime = 0;
    }
}
