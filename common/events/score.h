#ifndef TALLER_TP_SCORE_H
#define TALLER_TP_SCORE_H

#include "base/event.h"
#include <list>
#include <string>

class Score : public Event {
private:
  std::list<std::string> names;
  std::list<int> scores;

public:
  Score(std::list<std::string> names, const std::list<int>& scores);

  std::list<std::string> get_names() const override;

  std::list<int> get_scores() const override;
};

#endif // TALLER_TP_SCORE_H
