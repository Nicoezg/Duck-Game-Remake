#ifndef TALLER_TP_CHEAT_H
#define TALLER_TP_CHEAT_H

#include "cheat_macros.h"
#include "common/actions/base/action.h"

class Cheat : public Action {
private:
  int player_id;

  CheatId cheat_id;

public:
  Cheat(int player_id, CheatId cheat_id);

  CheatId get_cheat_id() const override;

  int get_player_id() const override;
};

#endif // TALLER_TP_CHEAT_H
