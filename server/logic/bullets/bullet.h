#ifndef BULLET_H
#define BULLET_H

#include "common/events/items/bullet_dto.h"
#include "common/events/items/bullet_macros.h"
#include "server/configs/configurations.h"
#include "server/logic/collisions/position.h"

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
    int traveledDistance;
    bool upwards;

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

    int getOwnerId() const;

    BulletDTO toDTO() const;

    bool impact(Position &other_position);

    bool impact(Position &other_position, int owner);
};

#endif // BULLET_H