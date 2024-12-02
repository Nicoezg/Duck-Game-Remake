//
// Created by fran on 04/11/24.
//

#include "new_player.h"

NewPlayer::NewPlayer(int actual_players, int max_players,
                     std::list<PlayerData> players_data)
    : Event(NEW_PLAYER), max_players(max_players),
      actual_players(actual_players), players_data(std::move(players_data)) {}

std::list<PlayerData> NewPlayer::get_players_data() const {
  return players_data;
}

int NewPlayer::get_max_players() const { return max_players; }

int NewPlayer::get_actual_players() const { return actual_players; }
