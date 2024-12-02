#include "laser_rifle.h"
#include "server/logic/duck.h"

#define NAME LASER_RIFLE_NAME
const int AMMO = CONFIG.getBulletConfig(NAME).getAmmo();
const int REACH = CONFIG.getBulletConfig(NAME).getReach();
const int COOLDOWN = CONFIG.getBulletConfig(NAME).getCooldown();

LaserRifle::LaserRifle(GameMap &map)
    : Weapon(map, AMMO, REACH, WeaponId::LASER_RIFLE) {
  shotCount = 0;
}

void LaserRifle::shoot(Duck *owner) {
  if (isReadyToShoot()) {

    int baseAngle = 45;
    int angle = (baseAngle + (shotCount));

    if (hasAmmo()) {
      createBullet(owner, -angle, true, reach, BulletId::LASER_BEAM);
      ammo--;
      lastShotTime = 0;
      shotCount++;
    } 
  }
}

void LaserRifle::replenishAmmo(){
  ammo = AMMO;
  shotCount = 0;
}