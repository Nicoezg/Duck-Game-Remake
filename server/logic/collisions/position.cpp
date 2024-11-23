//
// Created by fran on 23/11/24.
//

#include <string>
#include "position.h"


Position::Position(const Coordinate point, const CollisionRadius collision_radius)
        : point(point), collision_radius(collision_radius) {}

Position::Position(int x, int y, int radius_x, int radius_y) :
        point(x, y), collision_radius(radius_x, radius_y) {}

bool Position::is_colliding(const Coordinate &other_point) const {
    return collision_radius.is_colliding(point, other_point);
}

bool Position::is_colliding(const Position &position) const {
    return collision_radius.is_colliding(point, position) ||
           position.collision_radius.is_colliding(position.point, *this);
}

Position Position::operator+(const Coordinate &position) const {
    return {point + position, collision_radius};
}

Position &Position::operator=(const Coordinate newCoordinate) {
    point = newCoordinate;
    return *this;
}

std::string Position::print() const {
    return "Position: x: " + point.print() + " Collision radius: " + collision_radius.print();
}

