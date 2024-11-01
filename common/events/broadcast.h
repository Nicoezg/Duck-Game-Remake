//
// Created by fran on 24/10/24.
//

#ifndef TALLER_TP_BROADCAST_H
#define TALLER_TP_BROADCAST_H

#include "event.h"
#include "player.h"
#include <list>
#include <string>

class Broadcast : public Event {
private:
  std::list<Player> players;

public:
  explicit Broadcast(std::list<Player> &&players);

  std::list<Player> get_players() override;
};

#endif // TALLER_TP_BROADCAST_H
