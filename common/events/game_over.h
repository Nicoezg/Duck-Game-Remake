#ifndef TALLER_TP_GAME_OVER_H
#define TALLER_TP_GAME_OVER_H

#include <string>
#include <vector>
#include "base/event.h"

class GameOver : public Event {
private:
    PlayerData winner;
    int score;

public:
  GameOver(PlayerData winner, int scores);

  PlayerData get_winner() const override;

  int get_score() const override;

};

#endif // TALLER_TP_GAME_OVER_H
