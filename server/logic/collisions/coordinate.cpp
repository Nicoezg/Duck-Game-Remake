//
// Created by fran on 23/11/24.
//

#include "coordinate.h"

Coordinate::Coordinate(int x, int y) : x(x), y(y) {}

Coordinate Coordinate::operator+(const Coordinate &other) const {
    return {x + other.x, y + other.y};
}

Coordinate Coordinate::operator-(const Coordinate &other) const {
    return {x - other.x, y - other.y};
}

Coordinate Coordinate::operator*(const Coordinate &coordinate) const {
    return {x * coordinate.x, y * coordinate.y};
}

float Coordinate::square_norm(float a, float b) const {
    return (float(x * x) / (a * a)) + (float(y * y) / (b * b));
}

bool Coordinate::operator==(const Coordinate &coordinate) const {
    return x == coordinate.x && y == coordinate.y;
}

int Coordinate::operator[](int index) const {
    if (index == 0)
        return x;
    return y;
}

int Coordinate::operator[](char coord) const {
    if (coord == 'x')
        return x;
    return y;
}

bool Coordinate::operator!=(const Coordinate &coordinate) const {
    return x != coordinate.x || y != coordinate.y;
}

std::string Coordinate::print() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}