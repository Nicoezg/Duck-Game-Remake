//
// Created by fran on 23/11/24.
//

#ifndef TALLER_TP_COORDINATE_H
#define TALLER_TP_COORDINATE_H

#include "string"

class Coordinate {
private:
    int x;
    int y;

public:
    Coordinate(int x, int y);

    Coordinate operator+(const Coordinate &other) const;
    Coordinate operator-(const Coordinate &other) const;
    Coordinate operator*(const Coordinate &coordinate) const;
    float square_norm(float a, float b) const;

    bool operator==(const Coordinate &coordinate) const;
    bool operator!=(const Coordinate &coordinate) const;
    int operator[](int index) const;
    int operator[](char coord) const;

    std::string print() const;
};


#endif //TALLER_TP_COORDINATE_H
