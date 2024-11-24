//
// Created by fran on 24/10/24.
//

#ifndef TALLER_TP_BROADCAST_H
#define TALLER_TP_BROADCAST_H

#include "common/events/base/event.h"
#include "common/events/items/weapon_dto.h"
#include "items/bullet_dto.h"
#include "items/crate.h"
#include "items/explosion.h"
#include "items/item_spawn.h"
#include "player.h"
#include <list>
#include <string>

class Broadcast : public Event {
private:
  std::list<PlayerDTO> players;

  std::list<BulletDTO>
      bullets; // Incluye balas, bananas, granadas y explosiones

  std::list<CrateDTO> crates;

  std::list<ItemSpawnDTO> item_spawns; // Estos son los items que pueden aparecer en el mapa o al romper cajas.

  std::list<ExplosionDTO> explosions;

public:
  Broadcast(std::list<PlayerDTO> &&players, std::list<BulletDTO> &&bullets,
            std::list<CrateDTO> &&crates, std::list<ItemSpawnDTO> &&item_spawns,
            std::list<ExplosionDTO> &&explosions);

  Broadcast(std::list<PlayerDTO> &&players,  std::list<BulletDTO> &&bullets);

  std::list<PlayerDTO> get_players() const override;

  std::list<BulletDTO> get_bullets() const override;

  std::list<CrateDTO> get_crates() const override;

  std::list<ItemSpawnDTO> get_item_spawns() const override;

  std::list<ExplosionDTO> get_explosions() const override;
};

#endif // TALLER_TP_BROADCAST_H
