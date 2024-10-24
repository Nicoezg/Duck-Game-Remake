//
// Created by fran on 21/10/24.
//

#include "game_creation.h"

GameCreation::GameCreation(int game_code, int player_id_1, int player_id_2) :
    Event(CREATE_GAME), game_code(game_code), player_id_1(player_id_1), player_id_2(player_id_2) {}

int GameCreation::get_game_code() const {
    return game_code;
}

int GameCreation::get_player_id_1() const {
    return player_id_1;
}

int GameCreation::get_player_id_2() const {
    return player_id_2;
}

bool GameCreation::is_connected() const {
    return true;
}