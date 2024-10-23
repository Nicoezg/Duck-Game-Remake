//
// Created by fran on 21/10/24.
//

#include "game_creation.h"

GameCreation::GameCreation(int game_code, int player_id) : Event(CREATE_GAME), game_code(game_code), player_id(player_id) {}

int GameCreation::get_game_code() const {
    return game_code;
}

int GameCreation::get_player_id() const {
    return player_id;
}

bool GameCreation::is_connected() const {
    return true;
}