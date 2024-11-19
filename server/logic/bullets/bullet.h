#ifndef BULLET_H
#define BULLET_H

#include "common/events/items/bullet_macros.h"
#include "server/logic/configurations.h"

#define CONFIG Configurations::configurations()

class Bullet {
private:
  int owner_Id;
  int pos_x;
  int pos_y;
  float angle;
  int range;
  bool isGrenade;
  bool canBounce;
  BulletId id;
  bool isRight;
  bool upwards;
  int traveledDistance;

public:
  virtual ~Bullet() = default;

  Bullet(int owner_Id, int pos_x, int pos_y, float angle, bool canBounce,
         int range, BulletId id, bool isRight, bool upwards);

  void update();
  bool outOfRange();
  void bounce(int newAngle);
  int getPosX() const;
  int getPosY() const;
  float getAngle() const;
  BulletId getId() const;
};

#endif // BULLET_H