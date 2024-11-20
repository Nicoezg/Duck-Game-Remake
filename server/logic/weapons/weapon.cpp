#include "weapon.h"
#include "server/logic/duck.h"

void Weapon::createBullet(Duck *owner, int angle, bool canBounce, int reach,
                          BulletId id) {
  int posX = owner->getPositionX() + 10;
  int posY = owner->getPositionY() + 10;
  int ownerId = owner->getId();
  bool isRight = owner->getDirection();
  bool upwards = owner->isAimingUpwards();

  if (upwards) {
    angle = 90;
  }
  Bullet bullet(ownerId, posX, posY, angle, canBounce, reach, id, isRight, upwards);

  map.addBullet(std::make_unique<Bullet>(bullet));
}

WeaponId Weapon::getWeaponId() const { return id; }

void Weapon::createThrowable(Duck *owner,bool isGrenade) {
  if (isGrenade){
    map.addThrowable(std::make_unique<Grenade>(map,owner->getDirection(),owner->getPositionX(),owner->getPositionY()));
  }

}

bool Weapon::isReadyToShoot() const  { return !isReloading && hasAmmo() && cooldown == 0; }

void Weapon::increaseCooldown(int cooldownToAdd) {
      cooldown += cooldownToAdd;
      if (cooldown < 0){
        cooldown = 0;
      }
}

void Weapon::decreaseCooldown() {
  if (cooldown > 0){
    cooldown--;
  }
}