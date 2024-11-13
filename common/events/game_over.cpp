#include "game_over.h"

GameOver::GameOver(std::string &&winner, int &&score)
    : Event(GAME_OVER), winner(winner), score(score) {}

std::string GameOver::get_winner() const { return winner; }

int GameOver::get_score() const { return score; }

