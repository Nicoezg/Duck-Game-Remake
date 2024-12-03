#include "crate.h"

CrateDTO::CrateDTO(int position_x, int position_y, uint8_t hp, bool is_hit)
    : position_x(position_x), position_y(position_y), hp(hp), is_hit(is_hit) {}

uint8_t CrateDTO::get_hp() const { return hp; }

bool CrateDTO::was_hit() const { return is_hit; }

int CrateDTO::get_position_x() const { return position_x; }

int CrateDTO::get_position_y() const { return position_y; }
