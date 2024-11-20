#include "score.h"

Score::Score(std::vector<std::string> &&names, std::vector<int> &&scores)
    : Event(SCORE), names(std::move(names)), scores(std::move(scores)) {}

std::vector<std::string> Score::get_names() const { return names; }

std::vector<int> Score::get_scores() const { return scores; }

