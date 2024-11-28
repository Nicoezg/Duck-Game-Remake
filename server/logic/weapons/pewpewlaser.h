#ifndef PEWPEWLASER_H
#define PEWPEWLASER_H
#include "weapon.h"

class PewPewLaser : public Weapon {
public:
  explicit PewPewLaser(GameMap &map);

  void shoot(Duck *owner) override;

  void replenishAmmo() override;
};

#endif // PEWPEWLASER_H