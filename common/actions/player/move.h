#ifndef TALLER_TP_MOVE_H
#define TALLER_TP_MOVE_H

#include "common/actions/base/action.h"

class Move : public Action {
private:
  bool right;
  int player_id;

public:
  Move(int player_id, bool is_right);

  bool is_right() const override;

  int get_player_id() const override;
};

#endif // TALLER_TP_MOVE_H
