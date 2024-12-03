#ifndef TALLER_TP_THROWABLE_DTO_H
#define TALLER_TP_THROWABLE_DTO_H

#include "throwable_macros.h"
#include <cstdint>
#include <string>

class ThrowableDTO {
private:
  int position_x;
  int position_y;
  ThrowableId throwable_id;
  float angle;
  bool direction;
  bool action;

public:
  ThrowableDTO(int position_x, int position_y, ThrowableId throwable_id,
               float angle, bool direction, bool action);

  int get_position_x() const;

  int get_position_y() const;

  ThrowableId get_id() const;

  float get_angle() const;

  bool get_direction() const;

  bool get_action() const;
};

#endif // TALLER_TP_THROWABLE_DTO_H
