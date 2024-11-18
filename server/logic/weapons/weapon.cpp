#include "weapon.h"
#include "server/logic/duck.h"

void Weapon::createBullet(Duck *owner, int angle, bool canBounce, int reach,
                          BulletId id) {
  int posX = owner->getPositionX();
  int posY = owner->getPositionY();
  int ownerId = owner->getId();

  Bullet bullet(ownerId, posX, posY, angle, canBounce, reach, id);

  map.addBullet(std::make_unique<Bullet>(bullet));
}
