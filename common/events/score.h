#ifndef TALLER_TP_SCORE_H
#define TALLER_TP_SCORE_H

#include <string>
#include <list>
#include "base/event.h"

class Score : public Event {
private:
    std::list<std::string> names;
    std::list<int> scores;

public:
  Score(std::list<std::string> names, std::list<int> scores);

  std::list<std::string> get_names() const override;

  std::list<int> get_scores() const override;
};

#endif // TALLER_TP_SCORE_H
