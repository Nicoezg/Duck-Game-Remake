#ifndef AK47_H
#define AK47_H

#include "weapon.h"

class Ak47 : public Weapon {
public:
  explicit Ak47(GameMap &map);

  void shoot(Duck *owner) override;
};

#endif // AK47_H