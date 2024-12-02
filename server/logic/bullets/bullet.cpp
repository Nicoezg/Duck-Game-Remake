#include "bullet.h"
#include "common/events/items/bullet_dto.h"
#include "server/logic/hitBox.h"
#include <cmath>
#include <iostream>

const double PI = 3.14159265358979323846;
const int TILE_SIZE = 16;
const int SPEED = CONFIG.getBulletSpeed();
const int HEIGHT = CONFIG.getBulletConfig(SNIPER_NAME).getHeight();
const int WIDTH = CONFIG.getBulletConfig(SNIPER_NAME).getWidth();

Bullet::Bullet(int owner_Id, int pos_x, int pos_y, float angle, bool canBounce,
               int range, BulletId id, bool isRight, bool upwards)
    : owner_Id(owner_Id), pos_x(pos_x), pos_y(pos_y), angle(angle),
      range(range), canBounce(canBounce), id(id), isRight(isRight),
      traveledDistance(0), upwards(upwards) {}

void Bullet::update() {
  double radianAngle = angle * (PI / 180.0);

  int deltaX =
      static_cast<int>(CONFIG.getBulletSpeed() * std::cos(radianAngle));
  int deltaY = static_cast<int>(10 * std::sin(radianAngle));

  if (upwards) {
    pos_x -= deltaX;
    pos_y -= CONFIG.getBulletSpeed();
    ;
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

        if (isHorizontalCollision) {
            angle = 180 - angle;
        } else {
            if (isTopCollision) {
                angle = 360 - angle; 
            } else {
                angle = 180 - angle;
            }
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

/*bool Bullet::impact(Position &other_position) {
    Position position = Position(pos_x, pos_y, WIDTH, HEIGHT);
    bool is_impact = position.is_colliding(other_position);

    if (is_impact) {
        std::cout << "Impact" << std::endl;
    } else {
        std::cout << "No impact self: " << position.print() << " other: " << other_position.print() <<  std::endl;
    }
    return is_impact;
}

bool Bullet::impact(Position &other_position, int owner) {
    if (owner == owner_Id) {
        std::cout << "Owner impact" << std::endl;
        return false;
    }
    return impact(other_position);
} */
