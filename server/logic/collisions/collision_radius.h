//
// Created by fran on 23/11/24.
//

#ifndef TALLER_TP_COLLISION_RADIUS_H
#define TALLER_TP_COLLISION_RADIUS_H


#include "coordinate.h"
#include "vector"
#include "string"

class Position;

class CollisionRadius {
private:
    int radius_x;
    int radius_y;
    
public:
    CollisionRadius(int collisionRadiusX, int collisionRadiusY);

    std::vector<Coordinate> get_colliding_points(const Coordinate &reference) const;

    bool is_colliding(const Coordinate &reference, const Position &position) const;

    bool is_colliding(const Coordinate &reference, const Coordinate &point) const;

    Coordinate add_y_limit(const Coordinate &reference) const;

    Coordinate add_x_limit(const Coordinate &reference) const;

    Coordinate subtract_x_limit(const Coordinate &reference) const;

    Coordinate subtract_y_limit(const Coordinate &reference) const;

    std::vector<Coordinate> get_vertical_colliding_points(const Coordinate &reference) const;

    std::vector<Coordinate> get_horizontal_colliding_points(const Coordinate &reference) const;

    std::string print() const;
};


#endif //TALLER_TP_COLLISION_RADIUS_H
