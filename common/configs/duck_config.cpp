//
// Created by fran on 21/11/24.
//

#include "duck_config.h"

DuckConfig::DuckConfig(int speed_x, int speed_y, int flapping_speed,
                       int gravity, int width, int height, int center_x,
                       int center_y)
    : speed_x(speed_x), speed_y(speed_y), flapping_speed(flapping_speed),
      gravity(gravity), width(width), height(height), center_x(center_x),
      center_y(center_y) {}

int DuckConfig::getSpeedX() const { return speed_x; }

int DuckConfig::getSpeedY() const { return speed_y; }

int DuckConfig::getFlappingSpeed() const { return flapping_speed; }

int DuckConfig::getGravity() const { return gravity; }

int DuckConfig::getWidth() const { return width; }

int DuckConfig::getHeight() const { return height; }

int DuckConfig::getCenterX() const { return center_x; }

int DuckConfig::getCenterY() const { return center_y; }
