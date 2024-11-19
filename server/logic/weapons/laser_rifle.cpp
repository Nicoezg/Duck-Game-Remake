#include "laser_rifle.h"
#include "server/logic/duck.h"

LaserRifle::LaserRifle(GameMap &map)
    : Weapon(map, 30, 10, WeaponId::LASER_RIFLE) {
  reloadTime = 0.1f;
  shotCount = 0;
}

void LaserRifle::shoot(Duck *owner) {
  if (isReadyToShoot()) {

    int baseAngle = 45;
    int angle = baseAngle + (shotCount * 2);

    if (ammo > 0) {
      createBullet(owner, angle, true, reach, BulletId::LASER_BEAM);
      ammo--;
      lastShotTime = 0;
      shotCount++;
    }
  }
}