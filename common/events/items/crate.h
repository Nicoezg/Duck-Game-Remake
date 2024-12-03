#ifndef TALLER_TP_CRATE_H
#define TALLER_TP_CRATE_H

#include <cstdint>
#include <string>

class CrateDTO {
private:
  int position_x;
  int position_y;
  uint8_t hp;
  bool is_hit;

public:
  CrateDTO(int position_x, int position_y, uint8_t hp = 4, bool is_hit = false);

  uint8_t get_hp() const;

  bool was_hit() const;

  int get_position_x() const;

  int get_position_y() const;
};

#endif // TALLER_TP_CRATE_H
