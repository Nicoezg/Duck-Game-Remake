#ifndef SNIPER_H
#define SNIPER_H

#include "weapon.h"

class Sniper : public Weapon {
public:
  explicit Sniper(GameMap &map);

  void shoot(Duck *owner) override;
};

#endif // SNIPER_H