#ifndef TALLER_TP_ACTION_H
#define TALLER_TP_ACTION_H

#include "../player/cheat_macros.h"
#include "action_macros.h"
#include "common/game_mode.h"
#include <string>
#include <vector>

class Action {
private:
  ActionType type;

public:
  explicit Action(ActionType type);

  ActionType get_type() const;

  virtual ~Action() = default;

  virtual std::string get_player_name_1() const;

  virtual std::string get_player_name_2() const;

  virtual std::string get_game_name() const;

  virtual int get_player_id() const;

  virtual GameMode get_game_mode() const;

  virtual int get_game_code() const;

  virtual bool is_right() const;

  virtual bool is_playing_dead() const;

  virtual bool is_jumping_flapping() const;

  virtual bool is_aiming_upwards() const;

  virtual bool is_shooting() const;

  virtual bool is_picking_dropping() const;

  virtual int get_max_players() const;

  virtual bool is_still() const;

  virtual CheatId get_cheat_id() const;
};

#endif // TALLER_TP_ACTION_H
