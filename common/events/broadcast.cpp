//
// Created by fran on 24/10/24.
//

#include "broadcast.h"

#include <utility>

Broadcast::Broadcast(std::list<PlayerDTO> &&players, std::list<BulletDTO> &&bullets, std::list<CrateDTO> &&crates,
                     std::list<WeaponDTO> &&weapons, std::list<Explosion> &&explosions)
        : Event(BROADCAST), players(std::move(players)), bullets(std::move(bullets)), crates(std::move(crates)),
          weapons(std::move(weapons)), explosions(explosions) {}

std::list<PlayerDTO> Broadcast::get_players() const { return players; }

std::list<BulletDTO> Broadcast::get_bullets() const { return bullets; }

std::list<CrateDTO> Broadcast::get_crates() const { return crates; }

std::list<WeaponDTO> Broadcast::get_weapons() const { return weapons; }

std::list<Explosion> Broadcast::get_explosions() const { return explosions; }

Broadcast::Broadcast(std::list<PlayerDTO> &&players, std::list<BulletDTO> &&bullets) : Event(BROADCAST),
                                                                                       players(std::move(players)),
                                                                                       bullets(std::move(bullets)) {}
