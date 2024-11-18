#ifndef COWBOY_H
#define COWBOY_H
#include "weapon.h"

class Cowboy : public Weapon {
public:
  explicit Cowboy(GameMap &map);

  void shoot(Duck *owner) override;
};

#endif // COWBOY_H