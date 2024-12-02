//
// Created by fran on 21/11/24.
//

#ifndef TALLER_TP_BULLET_CONFIG_H
#define TALLER_TP_BULLET_CONFIG_H

class BulletConfig {
private:
  int ammo;
  int reach;
  int cooldown;
  int height;
  int width;

public:
  BulletConfig(int ammo, int reach, int cooldown, int height, int width);

  int getAmmo() const;

  int getReach() const;

  int getCooldown() const;

  int getHeight() const;

  int getWidth() const;
};

#endif // TALLER_TP_BULLET_CONFIG_H
