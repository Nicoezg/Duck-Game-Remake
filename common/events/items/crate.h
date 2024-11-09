#ifndef TALLER_TP_CRATE_H
#define TALLER_TP_CRATE_H

#include <cstdint>
#include <string>



class Crate {
private:
  int position_x;
  int position_y;
  uint8_t hp; // La "vida" de la caja. Si llega a 0, tira algo. Empieza con 4 de vida.


public:
  Crate(int position_x, int position_y, uint8_t hp);

  uint8_t get_hp() const;

  int get_position_x() const;

  int get_position_y() const;
};

#endif // TALLER_TP_CRATE_H
