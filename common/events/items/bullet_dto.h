#ifndef TALLER_TP_BULLET_DTO_H
#define TALLER_TP_BULLET_DTO_H

#include "bullet_macros.h"
#include <cstdint>
#include <string>

class BulletDTO {
private:
  int position_x;
  int position_y;
  BulletId bullet_id;
  float angle;
  bool direction;

public:
  BulletDTO(int position_x, int position_y, BulletId bullet_id, float angle,
            bool direction);

  int get_position_x() const;

  int get_position_y() const;

  BulletId get_id() const;

  float get_angle() const;

  bool get_direction() const;
};

#endif // TALLER_TP_BULLET_DTO_H
