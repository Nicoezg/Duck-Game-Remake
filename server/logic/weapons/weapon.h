#ifndef WEAPON_H
#define WEAPON_H

#include "common/events/items/weapon_macros.h"
#include "server/logic/bullets/bullet.h"
#include "server/logic/throwables/throwable.h"

#include <memory>

class Duck;
class GameMap;

class Weapon {
protected:
  GameMap &map;
  int ammo;
  int reloadTime;
  int lastShotTime;
  bool isReloading;
  int reach;
  WeaponId id;
  int cooldown;

public:
  Weapon(GameMap &map, int initialAmmo, int reach, enum WeaponId id)
      : map(map), ammo(initialAmmo), reloadTime(0), lastShotTime(0),
        isReloading(false), reach(reach), id(id), cooldown(0) {}

  virtual ~Weapon() = default;

  virtual void shoot(Duck *owner) = 0;

  bool hasAmmo() const { return ammo > 0; }
  int getAmmo() const { return ammo; }

  virtual bool isReadyToShoot() const;


  void createBullet(Duck *owner, int angle, bool canBounce, int reach,
                    BulletId id);

  void createThrowable(GameMap &map,Duck *owner,bool isGrenade);
  

  WeaponId getWeaponId() const;

    void increaseCooldown(int cooldownToAdd);
    void decreaseCooldown();

  virtual void replenishAmmo() = 0;
};

#endif // WEAPON_H
