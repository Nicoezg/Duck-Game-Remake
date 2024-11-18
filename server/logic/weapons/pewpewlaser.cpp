#include "pewpewlaser.h"

PewPewLaser::PewPewLaser(GameMap &map)
    : Weapon(map, CONFIG.getPewPewLaserAmmo(), CONFIG.getPewPewLaserReach(),
             WeaponId::PEW_PEW_LASER) {}

void PewPewLaser::shoot(Duck *owner) {
  ammo--;

  float angles[3] = {0.0f, 0.1f, -0.1f};
  for (float angle : angles) {
    createBullet(owner, angle, false, reach, BulletId::LASER_REBOUND);
  }

  lastShotTime = 0;
}
