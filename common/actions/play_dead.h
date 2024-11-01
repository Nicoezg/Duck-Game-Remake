#ifndef TALLER_TP_PLAY_DEAD_H
#define TALLER_TP_PLAY_DEAD_H

#include "action.h"

class PlayDead : public Action {
private:
  bool play_dead;
  int player_id;

public:
  PlayDead(int player_id, bool is_right);

  bool is_playing_dead() const override;

  int get_player_id() const override;
};

#endif // TALLER_TP_PLAY_DEAD_H
