//
// Created by fran on 04/11/24.
//

#include "game_room.h"

GameRoom::GameRoom(): game_code(0), max_players(0), actual_players(0) {}

GameRoom::GameRoom(int game_code, std::string game_name, int actual_players, int max_players) :
game_code(game_code), game_name(game_name), max_players(max_players), actual_players(actual_players) {}

std::string GameRoom::get_game_name() const {
    return game_name;
}

int GameRoom::get_game_code() const { return game_code; }

int GameRoom::get_max_players() const { return max_players; }

int GameRoom::get_actual_players() const { return actual_players; }
