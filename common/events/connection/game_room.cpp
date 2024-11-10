//
// Created by fran on 04/11/24.
//

#include "game_room.h"

GameRoom::GameRoom(int game_code, int actual_players, int max_players) : game_code(game_code), max_players(max_players),
                                                                       actual_players(actual_players) {}

int GameRoom::get_game_code() const { return game_code; }

int GameRoom::get_max_players() const { return max_players; }

int GameRoom::get_actual_players() const { return actual_players; }
