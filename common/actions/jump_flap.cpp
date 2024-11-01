#include "jump_flap.h"
#include "action.h"

JumpFlap::JumpFlap(int player_id, bool jump_flap)
    : Action(JUMP_FLAP), jump_flap(jump_flap), player_id(player_id) {}

bool JumpFlap::is_jumping_flapping() const { return jump_flap; }

int JumpFlap::get_player_id() const { return player_id; }
