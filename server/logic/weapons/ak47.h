#ifndef AK47_H
#define AK47_H

#include "weapon.h"

class Ak47 : public Weapon {
private:
  int consecutiveShots;
public:
  explicit Ak47(GameMap &map);

  void shoot(Duck *owner) override;

  void replenishAmmo() override;

  void resetConsecutiveShots() override;

  void increaseConsecutiveShots() override;
};

#endif // AK47_H