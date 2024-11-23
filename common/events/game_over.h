#ifndef TALLER_TP_GAME_OVER_H
#define TALLER_TP_GAME_OVER_H

#include <string>
#include <vector>
#include "base/event.h"

class GameOver : public Event {
private:
    int winner;
    int score;

public:
  GameOver(int winner, int scores);

  std::string get_winner() const override;

  int get_score() const override;

  int get_player_id_1() const override;
};

#endif // TALLER_TP_GAME_OVER_H
