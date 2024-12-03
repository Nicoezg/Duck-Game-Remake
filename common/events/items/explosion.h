#ifndef TALLER_TP_EXPLOSION_H
#define TALLER_TP_EXPLOSION_H

#include "bullet_macros.h"
#include <cstdint>
#include <string>

class ExplosionDTO {
private:
  int position_x;
  int position_y;
  uint8_t currentDuration;

public:
  ExplosionDTO(int position_x, int position_y, uint8_t currentDuration);

  int get_position_x() const;

  int get_position_y() const;

  uint8_t get_current_duration() const;
};

#endif // TALLER_TP_EXPLOSION_H
