//
// Created by fran on 21/11/24.
//

#include "duck_config.h"

DuckConfig::DuckConfig(int speed_x, int speed_y, int flapping_speed, int gravity) :
        speed_x(speed_x), speed_y(speed_y), flapping_speed(flapping_speed), gravity(gravity) {}

DuckConfig::DuckConfig() : speed_x(0), speed_y(0), flapping_speed(0), gravity(0) {}

int DuckConfig::getSpeedX() const {
    return speed_x;
}

int DuckConfig::getSpeedY() const {
    return speed_y;
}

int DuckConfig::getFlappingSpeed() const {
    return flapping_speed;
}

int DuckConfig::getGravity() const {
    return gravity;
}
