#include "explosion.h"


Explosion::Explosion(int position_x, int position_y, uint8_t currentDuration) 
: position_x(position_x), position_y(position_y), currentDuration(currentDuration) {}

uint8_t Explosion::get_current_duration() const { return currentDuration; }

int Explosion::get_position_x() const { return position_x; }

int Explosion::get_position_y() const { return position_y; }
