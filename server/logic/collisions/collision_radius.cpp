//
// Created by fran on 23/11/24.
//

#include "collision_radius.h"
#include <cmath>
#include <algorithm>
#include "position.h"


CollisionRadius::CollisionRadius(int radius_x, int radius_y)
        : radius_x(radius_x), radius_y(radius_y) {}

bool CollisionRadius::is_colliding(const Coordinate &reference,
                                   const Coordinate &point) const {
    if (radius_y == 0 && radius_x == 0) {
        return reference == point;
    } else if (radius_y == 0) {
        return reference['y'] == point['y'] && abs(reference['x'] - point['x']) <= radius_x;
    } else if (radius_x == 0) {
        return reference['x'] == point['x'] && abs(reference['y'] - point['y']) <= radius_y;
    }
    return (reference - point).square_norm(float(radius_x), float(radius_y)) <= 1;
}

bool CollisionRadius::is_colliding(const Coordinate &reference,
                                   const Position &position) const {

    std::vector<Coordinate> extremes = get_colliding_points(reference);

    return std::any_of(extremes.begin(), extremes.end(),
                       [&position](const Coordinate &extreme_point) {
                           return position.is_colliding(extreme_point);
                       });
}

/*
 * Devuelve los puntos extremos respecto al punto de referencia
 */
std::vector<Coordinate>
CollisionRadius::get_colliding_points(const Coordinate &reference) const {
    std::vector<Coordinate> colliding_points;

    if (radius_x > 0) {
        std::vector<Coordinate> horizontal_colliding_points = get_horizontal_colliding_points(reference);
        colliding_points.insert(colliding_points.end(), horizontal_colliding_points.begin(),
                                horizontal_colliding_points.end());
    }
    if (radius_y > 0) {
        std::vector<Coordinate> vertical_colliding_points = get_vertical_colliding_points(reference);
        colliding_points.insert(colliding_points.end(), vertical_colliding_points.begin(),
                                vertical_colliding_points.end());
    }
    return colliding_points;
}


std::vector<Coordinate> CollisionRadius::get_horizontal_colliding_points(
        const Coordinate &reference) const {

    std::vector<Coordinate> colliding_points;

    if (radius_x > 0) {
        colliding_points.push_back(add_x_limit(reference));
        colliding_points.push_back(subtract_x_limit(reference));
    }
    return colliding_points;
}

std::vector<Coordinate> CollisionRadius::get_vertical_colliding_points(
        const Coordinate &reference) const {
    std::vector<Coordinate> colliding_points;

    if (radius_y > 0) {
        colliding_points.push_back(add_y_limit(reference));
        colliding_points.push_back(subtract_y_limit(reference));
    }
    return colliding_points;
}

Coordinate CollisionRadius::add_y_limit(const Coordinate &reference) const {
    return {reference['x'], reference['y'] + radius_y};
}

Coordinate
CollisionRadius::subtract_y_limit(const Coordinate &reference) const {
    return {reference['x'], reference['y'] - radius_y};
}

Coordinate CollisionRadius::add_x_limit(const Coordinate &reference) const {
    return {reference['x'] + radius_x, reference['y']};
}

Coordinate
CollisionRadius::subtract_x_limit(const Coordinate &reference) const {
    return {reference['x'] - radius_x, reference['y']};
}

std::string CollisionRadius::print() const {
    return "(" + std::to_string(radius_x) + ", " + std::to_string(radius_y) + ")";
}

