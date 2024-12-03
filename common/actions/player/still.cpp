#include "still.h"
#include "common/actions/base/action.h"

Still::Still(int player_id, bool still)
    : Action(STILL), player_id(player_id), still(still) {}

bool Still::is_still() const { return still; }

int Still::get_player_id() const { return player_id; }
