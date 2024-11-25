#include "game_over.h"

GameOver::GameOver(PlayerData winner, int score)
    : Event(GAME_OVER), winner(winner), score(score) {}

PlayerData GameOver::get_winner() const { return winner; }

int GameOver::get_score() const { return score; }

