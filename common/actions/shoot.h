#ifndef TALLER_TP_SHOOT_H
#define TALLER_TP_SHOOT_H

#include "action.h"

class Shoot : public Action {
private:
  bool shooting;
  int player_id;

public:
  Shoot(int player_id, bool shooting);

  bool is_shooting() const override;

  int get_player_id() const override;
};

#endif // TALLER_TP_SHOOT_H
