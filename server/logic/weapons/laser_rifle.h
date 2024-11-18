#ifndef LASER_RIFLE_H
#define LASER_RIFLE_H

#include "weapon.h"

class LaserRifle : public Weapon {
private:
  int shotCount;

public:
  explicit LaserRifle(GameMap &map);

  void shoot(Duck *owner) override;
};

#endif // LASER_RIFLE_H