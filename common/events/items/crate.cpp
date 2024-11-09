#include "crate.h"


Crate::Crate(int position_x, int position_y, uint8_t hp = 4)
    : position_x(position_x), position_y(position_y), hp(hp) {}

uint8_t Crate::get_hp() const { return hp; }

int Crate::get_position_x() const { return position_x; }

int Crate::get_position_y() const { return position_y; }
