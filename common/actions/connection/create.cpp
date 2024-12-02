#include "create.h"
#include "common/actions/base/action.h"

#include <iostream>

#include "common/actions/base/action_macros.h"
#include "common/events/connection/game_creation.h"

Create::Create(GameMode game_mode, int max_players, std::string game_name,
               std::string player_name_1, std::string player_name_2)
    : Action(CREATE_REQUEST), game_mode(game_mode), max_players(max_players),
      game_name(game_name), player_name_1(player_name_1),
      player_name_2(player_name_2) {}

GameMode Create::get_game_mode() const { return game_mode; }

int Create::get_max_players() const { return max_players; }

std::string Create::get_player_name_1() const { return player_name_1; }

std::string Create::get_player_name_2() const { return player_name_2; }

std::string Create::get_game_name() const { return game_name; }
