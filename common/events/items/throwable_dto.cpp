#include "throwable_dto.h"

ThrowableDTO::ThrowableDTO(int position_x, int position_y,
                           ThrowableId throwable_id, float angle = 0,
                           bool direction = false, bool action = false)
    : position_x(position_x), position_y(position_y),
      throwable_id(throwable_id), angle(angle), direction(direction),
      action(action) {}

ThrowableId ThrowableDTO::get_id() const { return throwable_id; }

int ThrowableDTO::get_position_x() const { return position_x; }

int ThrowableDTO::get_position_y() const { return position_y; }

float ThrowableDTO::get_angle() const { return angle; }

bool ThrowableDTO::get_direction() const { return direction; }

bool ThrowableDTO::get_action() const { return action; }