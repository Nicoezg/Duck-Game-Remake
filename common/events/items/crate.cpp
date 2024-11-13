#include "crate.h"


Crate::Crate(int position_x, int position_y, uint8_t hp, bool is_hit)
    : position_x(position_x), position_y(position_y), hp(hp), is_hit(is_hit) {}

uint8_t Crate::get_hp() const { return hp; }

bool Crate::was_hit() const { return is_hit; }

int Crate::get_position_x() const { return position_x; }

int Crate::get_position_y() const { return position_y; }
