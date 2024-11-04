#ifndef TALLER_TP_CREATE_H
#define TALLER_TP_CREATE_H

#include "common/actions/base/action.h"
#include "common/actions/base/action_macros.h"
#include "common/game_mode.h"
#include <cstdint>
#include <string>

class Create : public Action {
private:
  GameMode game_mode;
  int max_players;

public:
  explicit Create(GameMode game_mode, int max_players);

  GameMode get_game_mode() const override;

    int get_max_players() const override;
};

#endif // TALLER_TP_CREATE_H
