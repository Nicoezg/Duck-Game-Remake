#ifndef BULLET_H
#define BULLET_H

#include "../../../common/configs/configurations.h"
#include "common/events/items/bullet_dto.h"
#include "common/events/items/bullet_macros.h"

class Bullet {
private:
  int owner_Id;
  int pos_x;
  int pos_y;
  float angle;
  int range;
  bool canBounce;
  BulletId id;
  bool isRight;
  int traveledDistance;
  bool upwards;
  int prev_pos_x;
  int prev_pos_y;

public:
  virtual ~Bullet() = default;

  Bullet(int owner_Id, int pos_x, int pos_y, float angle, bool canBounce,
         int range, BulletId id, bool isRight, bool upwards);

  void update();

  int getPrevPosX() const;

  int getPrevPosY() const;

  bool outOfRange();

  void bounce(bool isHorizontalCollision, bool isTopCollision);

  int getPosX() const;

  int getPosY() const;

  float getAngle() const;

  BulletId getId() const;

  int getOwnerId() const;

  BulletDTO toDTO() const;
};

#endif // BULLET_H