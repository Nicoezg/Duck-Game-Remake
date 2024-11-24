#include "weapon.h"
#include "server/logic/duck.h"
#include "server/logic/throwables/grenade.h"
#include "server/logic/throwables/banana.h"


void Weapon::createBullet(Duck *owner, int angle, bool canBounce, int reach,
                          BulletId id) {

  int posX;
  int posY;

  if (owner->isAimingUpwards()) {
    angle += 90;
    posX = owner->getPositionX() + 10;
    posY = owner->getPositionY() - 20;
  } else {
    if (owner->getDirection()) {
      posX = owner->getPositionX() + 15;
      posY = owner->getPositionY() + 15;
    } else if (!owner->getDirection()) {
      posX = owner->getPositionX() - 15;
      posY = owner->getPositionY() + 15;
    }
  }

  map.addBullet(std::make_unique<Bullet>(
      owner->getId(), posX, posY, angle, canBounce, reach, id,
      owner->getDirection(), owner->isAimingUpwards()));
}

WeaponId Weapon::getWeaponId() const { return id; }

void Weapon::createThrowable(GameMap &map,Duck *owner, bool isGrenade) {
  if (isGrenade) {
    map.addThrowable(std::make_unique<ThrownGrenade>(map, owner->getDirection(),owner->getPositionX(),
                                               owner->getPositionY(), 150));
  }else{
    map.addThrowable(std::make_unique<ThrownBanana>(map, owner->getDirection(),owner->getPositionX(),
                                               owner->getPositionY(), 150));
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
