#ifndef TALLER_TP_STILL_H
#define TALLER_TP_STILL_H

#include "common/actions/base/action.h"

class Still : public Action {
private:
  int player_id;
  bool still;
  

public:
  Still(int player_id, bool still);

  bool is_still() const override;

  int get_player_id() const override;
};

#endif // TALLER_TP_SHOOT_H
