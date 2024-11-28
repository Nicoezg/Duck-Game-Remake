#include "score.h"

Score::Score(std::list<std::string> &&names, std::list<int> &&scores)
    : Event(SCORE), names(std::move(names)), scores(std::move(scores)) {}

std::list<std::string> Score::get_names() const { return names; }

std::list<int> Score::get_scores() const { return scores; }

