#include "weapon.h"
#include "server/logic/duck.h"

void Weapon::createBullet(Duck *owner, int angle, bool canBounce, int reach,
                          BulletId id) {
  int posX = owner->getPositionX() + 15;
  int posY = owner->getPositionY() + 15;

  if (owner->isAimingUpwards()) {
    angle = angle + 90;
    posX = owner->getPositionX();
    posY = owner->getPositionY() -15;
  }

  map.addBullet(std::make_unique<Bullet>(owner->getId(), posX, posY, angle, canBounce, reach, id, owner->getDirection()));
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
