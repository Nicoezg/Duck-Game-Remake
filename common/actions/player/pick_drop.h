#ifndef TALLER_TP_PICK_DROP_H
#define TALLER_TP_PICK_DROP_H

#include "common/actions/base/action.h"

class PickDrop : public Action {
private:
  bool picking_dropping;
  int player_id;

public:
  PickDrop(int player_id, bool picking_dropping);

  bool is_picking_dropping() const override;

  int get_player_id() const override;
};

#endif // TALLER_TP_PICK_DROP_H
