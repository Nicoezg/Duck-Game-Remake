#ifndef GRENADE_H
#define GRENADE_H

#include "server/logic/throwables/grenade.h"
#include "weapon.h"

class Grenade : public Weapon {
  bool dropped = false;
  bool unplugged = false;

public:
  explicit Grenade(GameMap &map);

  void shoot(Duck *owner) override;

  void replenishAmmo() override;
};

#endif // GRENADE_H
