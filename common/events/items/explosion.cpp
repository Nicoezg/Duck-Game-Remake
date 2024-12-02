#include "explosion.h"

ExplosionDTO::ExplosionDTO(int position_x, int position_y,
                           uint8_t currentDuration)
    : position_x(position_x), position_y(position_y),
      currentDuration(currentDuration) {}

uint8_t ExplosionDTO::get_current_duration() const { return currentDuration; }

int ExplosionDTO::get_position_x() const { return position_x; }

int ExplosionDTO::get_position_y() const { return position_y; }
