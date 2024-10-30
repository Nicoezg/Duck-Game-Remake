#ifndef TALLER_TP_AIM_UPWARDS_H
#define TALLER_TP_AIM_UPWARDS_H

#include "action.h"

class AimUpwards : public Action {
private:
  bool aiming_upwards;
  int player_id;

public:
  AimUpwards(int player_id, bool aiming_upwards);

  bool is_aiming_upwards() const override;

  int get_player_id() const override;
};

#endif // TALLER_TP_AIM_UPWARDS_H
