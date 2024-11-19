#include "bullet.h"
#include <cmath>

const double PI = 3.14159265358979323846;

Bullet::Bullet(int owner_Id, int pos_x, int pos_y, float angle, bool canBounce,
               int range, BulletId id, bool isRight, bool upwards)
    : owner_Id(owner_Id), pos_x(pos_x), pos_y(pos_y), angle(angle),
      range(range), canBounce(canBounce), id(id), isRight(isRight), upwards(upwards) {}

void Bullet::update() {
  double radianAngle = angle * (PI / 180.0);

  int deltaX =
      static_cast<int>(CONFIG.getBulletSpeed() * std::cos(radianAngle));
  int deltaY =
      static_cast<int>(10 * std::sin(radianAngle));

  if (upwards) {
    pos_y -= CONFIG.getBulletSpeed();
  } else {
    if (isRight) {
      pos_x += deltaX;
      pos_y += deltaY; 
    } else {
      pos_x -= deltaX;
      pos_y += deltaY;
    }
  }
  
}

void Bullet::bounce(int newAngle) { angle = newAngle; }

int Bullet::getPosX() const { return pos_x; }

int Bullet::getPosY() const { return pos_y; }

float Bullet::getAngle() const { return angle; }

BulletId Bullet::getId() const { return id; }
