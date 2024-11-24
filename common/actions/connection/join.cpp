//
// Created by fran on 21/10/24.
//

#include "join.h"
#include "common/actions/base/action.h"
#include "create.h"
#include <iostream>
#include <stdexcept>

Join::Join(int &game_code, GameMode game_mode, std::string &player_name_1, std::string &player_name_2)
        : Action(JOIN_REQUEST), game_code(game_code), game_mode(game_mode), player_name_1(player_name_1), player_name_2(player_name_2) {}

int Join::get_game_code() const { return game_code; }

GameMode Join::get_game_mode() const { return game_mode; }

std::string Join::get_player_name_1() const { return player_name_1; }

std::string Join::get_player_name_2() const { return player_name_2; }