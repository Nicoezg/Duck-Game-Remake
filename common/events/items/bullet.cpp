#include "bullet.h"


Bullet::Bullet(int position_x, int position_y, BulletId bullet_id, float angle = 0)
    : position_x(position_x), position_y(position_y), bullet_id(bullet_id), angle(angle){}

BulletId Bullet::get_id() const { return bullet_id; }

int Bullet::get_position_x() const { return position_x; }

int Bullet::get_position_y() const { return position_y; }

float Bullet::get_angle() const { return angle; }
