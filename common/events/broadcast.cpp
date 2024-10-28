//
// Created by fran on 24/10/24.
//

#include "broadcast.h"

#include <utility>

Broadcast::Broadcast(std::list<Player> &&players)
    : Event(BROADCAST), players(std::move(players)) {}

std::list<Player> Broadcast::get_players() { return players; }
