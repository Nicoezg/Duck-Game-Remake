#include "game_over.h"

GameOver::GameOver(int winner, int score)
    : Event(GAME_OVER), winner(winner), score(score) {}

std::string GameOver::get_winner() const { return "Player " + std::to_string(winner); }

int GameOver::get_score() const { return score; }


int GameOver::get_player_id_1() const {
    return winner;
}