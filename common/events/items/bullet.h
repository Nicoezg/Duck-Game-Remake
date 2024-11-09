#ifndef TALLER_TP_BULLET_H
#define TALLER_TP_BULLET_H

#include <cstdint>
#include <string>
#include "bullet_macros.h"

class Bullet {
private:
  int position_x;
  int position_y;
  BulletId bullet_id;
  float angle;


public:
  Bullet(int position_x, int position_y, BulletId bullet_id, float angle);

  int get_position_x() const;

  int get_position_y() const;

  BulletId get_id() const;

  float get_angle() const;
};

#endif // TALLER_TP_BULLET_H
