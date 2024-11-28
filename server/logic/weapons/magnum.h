#ifndef MAGNUM_H
#define MAGNUM_H

#include "weapon.h"

class Magnum : public Weapon {
public:
  explicit Magnum(GameMap &map);

  void shoot(Duck *owner) override;

  void replenishAmmo() override;
};

#endif // MAGNUM_H
