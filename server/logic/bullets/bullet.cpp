#include "bullet.h"
#include "common/events/items/bullet_dto.h"
#include "server/logic/hitBox.h"
#include <cmath>
#include <iostream>

const double PI = 3.14159;
const int TILE_SIZE = 16;
const int SPEED_X = CONFIG.getBulletSpeedX();
const int SPEED_Y = CONFIG.getBulletSpeedY();
const int HEIGHT = CONFIG.getBulletConfig(SNIPER_NAME).getHeight();
const int WIDTH = CONFIG.getBulletConfig(SNIPER_NAME).getWidth();
const int HORIZONTAL_ANGLE = 180;

Bullet::Bullet(int owner_Id, int pos_x, int pos_y, float angle, bool canBounce,
               int range, BulletId id, bool isRight, bool upwards)
    : owner_Id(owner_Id), pos_x(pos_x), pos_y(pos_y), angle(angle),
      range(range), canBounce(canBounce), id(id), isRight(isRight),
      traveledDistance(0), upwards(upwards), prev_pos_x(0), prev_pos_y(0) {}

void Bullet::update() {

  prev_pos_x = pos_x;
  prev_pos_y = pos_y;

  double radianAngle = angle * (PI / HORIZONTAL_ANGLE);

  int deltaX = static_cast<int>(SPEED_X * std::cos(radianAngle));
  int deltaY = static_cast<int>(SPEED_Y * std::sin(radianAngle));

  if (upwards) {
    pos_x -= deltaX;
    pos_y -= SPEED_Y;
  } else if (isRight) {
    pos_x += deltaX;
    pos_y += deltaY;
  } else {
    pos_x -= deltaX;
    pos_y -= deltaY;
  }

  if (id == BulletId::LASER_REBOUND) {
    id = BulletId::LASER_BEAM;
  }

  int distanceMoved = std::sqrt(deltaX * deltaX + deltaY * deltaY);
  traveledDistance += distanceMoved;
}

int Bullet::getPrevPosX() const { return prev_pos_x; }
int Bullet::getPrevPosY() const { return prev_pos_y; }

bool Bullet::outOfRange() {
  int tilesMoved = traveledDistance / TILE_SIZE;
  if (tilesMoved >= range) {
    return true;
  }
  return false;
}

void Bullet::bounce(bool isHorizontalCollision, bool isTopCollision) {
  if (canBounce) {
    id = BulletId::LASER_REBOUND;

    if (isTopCollision) {
      angle = 360 - angle;
    } else if (isHorizontalCollision) {
      angle = HORIZONTAL_ANGLE - angle;
    }

    if (angle < 0) {
      angle += 360;
    } else if (angle >= 360) {
      angle -= 360;
    }
  }
}

int Bullet::getPosX() const { return pos_x; }

int Bullet::getPosY() const { return pos_y; }

float Bullet::getAngle() const { return angle; }

BulletId Bullet::getId() const { return id; }

int Bullet::getOwnerId() const { return owner_Id; }

BulletDTO Bullet::toDTO() const { return {pos_x, pos_y, id, angle, isRight}; }
