#include "cheat.h"


Cheat::Cheat(int player_id, CheatId cheat_id) : Action(CHEAT),player_id(player_id), cheat_id(cheat_id) {}

CheatId Cheat::get_cheat_id() const { return cheat_id; }

int Cheat::get_player_id() const { return player_id; }