//
// Created by fran on 24/10/24.
//

#ifndef TALLER_TP_BROADCAST_H
#define TALLER_TP_BROADCAST_H

#include "common/events/base/event.h"
#include "player.h"
#include "items/bullet.h"
#include "items/weapon.h"
#include "items/crate.h"
#include <list>
#include <string>

class Broadcast : public Event {
private:
  std::list<Player> players;

  std::list<Bullet> bullets; // Incluye balas, bananas, granadas y explosiones

  std::list<Crate> crates;

  std::list<Weapon> weapons; // Estos weapons son los que spawnean en el mapa

public:
  explicit Broadcast(std::list<Player> &&players, std::list<Bullet> &&bullets, std::list<Crate> &&crates, std::list<Weapon> &&weapons);

  std::list<Player> get_players() const override;

  std::list<Bullet> get_bullets() const override;

  std::list<Crate> get_crates() const override;

  std::list<Weapon> get_weapons() const override;
};

#endif // TALLER_TP_BROADCAST_H
