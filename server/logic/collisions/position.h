//
// Created by fran on 23/11/24.
//

#ifndef TALLER_TP_POSITION_H
#define TALLER_TP_POSITION_H


#include "coordinate.h"
#include "collision_radius.h"

class Position {

private:
    Coordinate point;
    CollisionRadius collision_radius;


public:
    Position(Coordinate coordinate, CollisionRadius collisionRadius);
    Position(int x, int y, int radius_x, int radius_y);

    bool is_colliding(const Position &position) const;

    bool is_colliding(const Coordinate &point) const;

    Position operator+(const Coordinate &position) const;

    Position &operator=(Coordinate position);

    std::string print() const;

};


#endif //TALLER_TP_POSITION_H
