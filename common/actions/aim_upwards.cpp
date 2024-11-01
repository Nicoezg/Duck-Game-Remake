#include "aim_upwards.h"
#include "action.h"

AimUpwards::AimUpwards(int player_id, bool aiming_upwards)
    : Action(AIM_UPWARDS), aiming_upwards(aiming_upwards), player_id(player_id) {}

bool AimUpwards::is_aiming_upwards() const { return aiming_upwards; }

int AimUpwards::get_player_id() const { return player_id; }
