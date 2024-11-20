#include "weapon.h"

class PewPewLaser : public Weapon {
public:
  explicit PewPewLaser(GameMap &map);

  void shoot(Duck *owner) override;
};
