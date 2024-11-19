#ifndef DUELOS_H
#define DUELOS_H

#include "server/logic/bullets/bullet.h"
#include "weapon.h"
#include <vector>

class Duelos : public Weapon {
public:
  explicit Duelos(GameMap &map);

  void shoot(Duck *shooter) override;
};

#endif // DUELOS_H
