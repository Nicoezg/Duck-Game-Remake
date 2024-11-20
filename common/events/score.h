#ifndef TALLER_TP_SCORE_H
#define TALLER_TP_SCORE_H

#include <string>
#include <vector>
#include "base/event.h"

class Score : public Event {
private:
    std::vector<std::string> names;

    std::vector<int> scores;


public:
  Score(std::vector<std::string> &&names, std::vector<int> &&scores);

  std::vector<std::string> get_names() const override;

  std::vector<int> get_scores() const override;
};

#endif // TALLER_TP_SCORE_H
