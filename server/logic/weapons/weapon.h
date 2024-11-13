#ifndef WEAPON_H
#define WEAPON_H

#include "server/logic/configurations.h"

#define CONFIG Configurations::configurations()

class Duck;

class Weapon {
protected:
  int reach;
  int ammo;
  bool reloading;
  int lastShot;

public:
  Weapon(int ammo, int reach)
      : reach(reach), ammo(ammo), reloading(false), lastShot(0) {}
  virtual ~Weapon() = default;

  virtual bool shoot(Duck *shooter) = 0;
  virtual bool canShoot() { return !isReloading() && hasAmmo(); }
  virtual void reload() = 0;

  bool hasAmmo() { return ammo > 0; }
  int getAmmo() const;
  int getReach() const;
  bool isReloading() const;
};

#endif // WEAPON_H
