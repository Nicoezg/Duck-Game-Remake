#include "bullet_dto.h"

BulletDTO::BulletDTO(int position_x, int position_y, BulletId bullet_id,
                     float angle = 0, bool direction = false)
    : position_x(position_x), position_y(position_y), bullet_id(bullet_id),
      angle(angle), direction(direction) {}

BulletId BulletDTO::get_id() const { return bullet_id; }

int BulletDTO::get_position_x() const { return position_x; }

int BulletDTO::get_position_y() const { return position_y; }

float BulletDTO::get_angle() const { return angle; }

bool BulletDTO::get_direction() const { return direction; }