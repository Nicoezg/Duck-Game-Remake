#include "weapon.h"

class PewPewLaser : public Weapon {
public:
  PewPewLaser()
      : Weapon(CONFIG.getPewPewLaserAmmo(), CONFIG.getPewPewLaserReach()) {}

  bool shoot(Duck *shooter) override {
    if (!canShoot())
      return false;

    ammo--;

    float angles[3] = {0.0f, 0.1f, -0.1f};
    for (float angle : angles) {
      // createProjectile(shooter, angle);
    }

    lastShot = 0;
    return true;
  }

  void reload() override { reloading = false; }
};
