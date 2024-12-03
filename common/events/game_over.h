#ifndef TALLER_TP_GAME_OVER_H
#define TALLER_TP_GAME_OVER_H

#include "base/event.h"
#include <string>
#include <vector>

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
