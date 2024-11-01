#ifndef TALLER_TP_CREATE_H
#define TALLER_TP_CREATE_H

#include "action.h"
#include "action_macros.h"
#include "common/game_mode.h"
#include <cstdint>
#include <string>

class Create : public Action {
private:
  GameMode game_mode;

public:
  explicit Create(GameMode game_mode);

  GameMode get_game_mode() const override;
};

#endif // TALLER_TP_CREATE_H
