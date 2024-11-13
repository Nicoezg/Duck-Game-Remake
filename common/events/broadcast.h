//
// Created by fran on 24/10/24.
//

#ifndef TALLER_TP_BROADCAST_H
#define TALLER_TP_BROADCAST_H

#include "common/events/base/event.h"
#include "player.h"
#include "items/bullet.h"
#include "common/events/items/weapon_dto.h"
#include "items/crate.h"
#include <list>
#include <string>

class Broadcast : public Event {
private:
    std::list<PlayerDTO> players;

    std::list<BulletDTO> bullets; // Incluye balas, bananas, granadas y explosiones

    std::list<CrateDTO> crates;

    std::list<WeaponDTO> weapons; // Estos weapons son los que spawnean en el mapa

public:
    Broadcast(std::list<PlayerDTO> &&players, std::list<BulletDTO> &&bullets, std::list<CrateDTO> &&crates,
              std::list<WeaponDTO> &&weapons);

    explicit Broadcast(std::list<PlayerDTO> &&players);

    std::list<PlayerDTO> get_players() override;

    std::list<BulletDTO> get_bullets() override;

    std::list<CrateDTO> get_crates() override;

    std::list<WeaponDTO> get_weapons() override;
};

#endif // TALLER_TP_BROADCAST_H
