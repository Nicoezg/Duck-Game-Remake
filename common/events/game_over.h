#ifndef TALLER_TP_GAME_OVER_H
#define TALLER_TP_GAME_OVER_H

#include <string>
#include <vector>
#include "base/event.h"

class GameOver : public Event {
private:
    std::string winner;
    int score;


public:
  GameOver(std::string &&winner, int &&scores);

  std::string get_winner() const override;

  int get_score() const override;
};

#endif // TALLER_TP_GAME_OVER_H
