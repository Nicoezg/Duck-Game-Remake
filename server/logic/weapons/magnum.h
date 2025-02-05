#ifndef MAGNUM_H
#define MAGNUM_H

#include "weapon.h"

class Magnum : public Weapon {
private:
  int consecutiveShots;

public:
  explicit Magnum(GameMap &map);

  void shoot(Duck *owner) override;

  void replenishAmmo() override;

  void resetConsecutiveShots() override;

  void increaseConsecutiveShots() override;
};

#endif // MAGNUM_H
