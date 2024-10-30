#include "pick_drop.h"
#include "action.h"

PickDrop::PickDrop(int player_id, bool picking_dropping)
    : Action(PICK_DROP), picking_dropping(picking_dropping), player_id(player_id) {}

bool PickDrop::is_picking_dropping() const { return picking_dropping; }

int PickDrop::get_player_id() const { return player_id; }
