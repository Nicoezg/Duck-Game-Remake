#ifndef GRENADE_H
#define GRENADE_H

#include "weapon.h"

class Grenade : public Weapon {
private:
  bool isArmed;         
  int framesToExplode; 

public:
  Grenade(GameMap &map);

  void shoot(Duck *owner) override;
  
};

#endif // GRENADE_H
