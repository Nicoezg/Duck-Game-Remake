#ifndef GRENADE_H
#define GRENADE_H

#include "weapon.h"
#include "server/logic/throwables/grenade.h"

class Grenade : public Weapon {
  bool dropped = false;
  bool unplugged =false;

public:
  Grenade(GameMap &map);

  void shoot(Duck *owner) override;

  void replenishAmmo() override;
  
};

#endif // GRENADE_H
