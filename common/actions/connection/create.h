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
  std::string game_name;
  std::string player_name_1;
  std::string player_name_2;

public:
  explicit Create(GameMode game_mode, int max_players, std::string game_name,
                  const std::string &player_name_1,
                  const std::string &player_name_2);

  GameMode get_game_mode() const override;

  int get_max_players() const override;

  std::string get_player_name_1() const override;

  std::string get_player_name_2() const override;

  std::string get_game_name() const override;
};

#endif // TALLER_TP_CREATE_H
