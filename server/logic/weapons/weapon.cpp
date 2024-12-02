#include "weapon.h"
#include "server/logic/duck.h"
#include "server/logic/throwables/grenade.h"
#include "server/logic/throwables/banana.h"
#include <iostream>

const int ANGLE_ADJUSTMENT = 90;
const int POS_X_UPWARDS_ADJUSTMENT = 10;
const int POS_X_ADJUSTMENT = 15;
const int POS_Y_ADJUSTMENT = 20;


void Weapon::createBullet(Duck *owner, int angle, bool canBounce, int reach,
                          BulletId id) {

  int posX;
  int posY;

  
  if (owner->isAimingUpwards()) {
    angle += ANGLE_ADJUSTMENT;
    posY = owner->getPositionY() - POS_Y_ADJUSTMENT;
    if (owner->getDirection()) {
      posX = owner->getPositionX() + POS_X_UPWARDS_ADJUSTMENT;
    } else {
      posX = owner->getPositionX() - POS_X_UPWARDS_ADJUSTMENT;
    }
  } else {
    posY = owner->getPositionY() + POS_Y_ADJUSTMENT;
    if (owner->getDirection()) {
      if (angle != 0) {
        angle = -angle;
      }
      posX = owner->getPositionX() + POS_X_ADJUSTMENT;
    } else if (!owner->getDirection()) {
      posX = owner->getPositionX() - POS_X_ADJUSTMENT;
    }
  }

  map.addBullet(std::make_unique<Bullet>(
      owner->getId(), posX, posY, angle, canBounce, reach, id,
      owner->getDirection(), owner->isAimingUpwards()));
}

WeaponId Weapon::getWeaponId() const { return id; }

void Weapon::createThrowable(GameMap &map,Duck *owner, bool isGrenade,int framesToExplode) {  
  if (isGrenade) {
    map.addThrowable(std::make_unique<ThrownGrenade>(map, owner->getDirection(),owner->getPositionX(),
                                               owner->getPositionY(), framesToExplode,owner->isAimingUpwards()));
  }else{
    map.addThrowable(std::make_unique<ThrownBanana>(map, owner->getDirection(),owner->getPositionX(),
                                               owner->getPositionY(), owner->isAimingUpwards()));
  }
}
bool Weapon::isReadyToShoot() const {
  return !isReloading && hasAmmo() && cooldown == 0;
}

void Weapon::increaseCooldown(int cooldownToAdd) {
  cooldown += cooldownToAdd;
  if (cooldown < 0) {
    cooldown = 0;
  }
}

void Weapon::decreaseCooldown() {
  if (cooldown > 0) {
    cooldown--;
  }
}

void Weapon::reload(){
  isReloading = false;
}
