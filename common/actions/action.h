#ifndef TALLER_TP_ACTION_H
#define TALLER_TP_ACTION_H

#include "action_macros.h"
#include "common/game_mode.h"
#include <string>

class Action {
private:
  ActionType type;

public:
  explicit Action(ActionType type);

  ActionType get_type() const;

  virtual ~Action() = default;

  virtual int get_player_id() const;

  virtual GameMode get_game_mode() const;

  virtual int get_game_code() const;

  virtual bool is_right() const;
};

#endif // TALLER_TP_ACTION_H
