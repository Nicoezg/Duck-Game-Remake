#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "weapon.h"

class Shotgun : public Weapon {
public:
  explicit Shotgun(GameMap &map);

  void shoot(Duck *owner) override;
};

#endif // SHOTGUN_H