//
// Created by fran on 24/10/24.
//

#include "move.h"
#include "action.h"
#include "create.h"
#include <stdexcept>

Move::Move(int player_id, bool right)
    : Action(MOVE), right(right), player_id(player_id) {}

bool Move::is_right() const { return right; }

int Move::get_player_id() const { return player_id; }
