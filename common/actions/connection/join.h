//
// Created by fran on 21/10/24.
//

#ifndef TALLER_TP_JOIN_H
#define TALLER_TP_JOIN_H

#include "common/actions/base/action.h"
#include "common/actions/base/action_macros.h"
#include "common/game_mode.h"
#include <cstdint>
#include <string>

class Join : public Action {
private:
  int game_code;
  GameMode game_mode;
  std::string player_name_1;
  std::string player_name_2;

public:
  explicit Join(int &game_code, GameMode game_mode, std::string &player_name_1,
                std::string &player_name_2);

  int get_game_code() const override;

  GameMode get_game_mode() const override;

  std::string get_player_name_1() const override;

  std::string get_player_name_2() const override;
};

#endif // TALLER_TP_JOIN_H
