#ifndef TALLER_TP_EXPLOSION_H
#define TALLER_TP_EXPLOSION_H

#include <cstdint>
#include <string>
#include "bullet_macros.h"

class Explosion {
private:
  int position_x;
  int position_y;
  uint8_t currentDuration; // Duracion actual de la explosión, va de 0 a 5.


public:
  Explosion(int position_x, int position_y, uint8_t currentDuration);

  int get_position_x() const;

  int get_position_y() const;

  uint8_t get_current_duration() const;
};

#endif // TALLER_TP_EXPLOSION_H
