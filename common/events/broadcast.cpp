//
// Created by fran on 24/10/24.
//

#include "broadcast.h"

#include <utility>

Broadcast::Broadcast(std::list<PlayerDTO> &&players, std::list<BulletDTO> &&bullets, std::list<CrateDTO> &&crates,
                     std::list<ItemSpawnDTO> &&item_spawns, std::list<ExplosionDTO> &&explosions)
        : Event(BROADCAST), players(std::move(players)), bullets(std::move(bullets)), crates(std::move(crates)),
          item_spawns(std::move(item_spawns)), explosions(explosions) {}

std::list<PlayerDTO> Broadcast::get_players() const { return players; }

std::list<BulletDTO> Broadcast::get_bullets() const { return bullets; }

std::list<CrateDTO> Broadcast::get_crates() const { return crates; }

std::list<ItemSpawnDTO> Broadcast::get_item_spawns() const { return item_spawns; }

std::list<ExplosionDTO> Broadcast::get_explosions() const { return explosions; }

Broadcast::Broadcast(std::list<PlayerDTO> &&players, std::list<BulletDTO> &&bullets) : Event(BROADCAST),
                                                                                       players(std::move(players)),
                                                                                       bullets(std::move(bullets)) {}
