#ifndef TALLER_TP_JUMP_FLAP_H
#define TALLER_TP_JUMP_FLAP_H

#include "common/actions/base/action.h"

class JumpFlap : public Action {
private:
  bool jump_flap;
  int player_id;

public:
  JumpFlap(int player_id, bool is_right);

  bool is_jumping_flapping() const override;

  int get_player_id() const override;
};

#endif // TALLER_TP_JUMP_FLAP_H
