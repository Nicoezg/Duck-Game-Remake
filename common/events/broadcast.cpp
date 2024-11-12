//
// Created by fran on 24/10/24.
//

#include "broadcast.h"

#include <utility>

Broadcast::Broadcast(std::list<Player> &&players, std::list<Bullet> &&bullets, std::list<Crate> &&crates, std::list<Weapon> &&weapons)
    : Event(BROADCAST), players(std::move(players)), bullets(std::move(bullets)), crates(std::move(crates)), weapons(std::move(weapons)) {}

std::list<Player> Broadcast::get_players() const { return players; }

std::list<Bullet> Broadcast::get_bullets() const { return bullets; }

std::list<Crate> Broadcast::get_crates() const { return crates; }

std::list<Weapon> Broadcast::get_weapons() const { return weapons; }
