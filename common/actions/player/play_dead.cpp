#include "play_dead.h"
#include "common/actions/base/action.h"

PlayDead::PlayDead(int player_id, bool play_dead)
    : Action(PLAY_DEAD), play_dead(play_dead), player_id(player_id) {}

bool PlayDead::is_playing_dead() const { return play_dead; }

int PlayDead::get_player_id() const { return player_id; }
