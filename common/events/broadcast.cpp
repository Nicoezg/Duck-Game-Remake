//
// Created by fran on 24/10/24.
//

#include "broadcast.h"

#include <utility>

Broadcast::Broadcast(std::list<PlayerDTO> &&players, std::list<BulletDTO> &&bullets, std::list<CrateDTO> &&crates, std::list<WeaponDTO> &&weapons)
    : Event(BROADCAST), players(std::move(players)), bullets(std::move(bullets)), crates(std::move(crates)), weapons(std::move(weapons)) {}

std::list<PlayerDTO> Broadcast::get_players() { return players; }

std::list<BulletDTO> Broadcast::get_bullets() { return bullets; }

std::list<CrateDTO> Broadcast::get_crates() { return crates; }

std::list<WeaponDTO> Broadcast::get_weapons() { return weapons; }

Broadcast::Broadcast(std::list<PlayerDTO> &&players) : Event(BROADCAST), players(std::move(players)) {}
