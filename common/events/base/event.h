//
// Created by fran on 21/10/24.
//

#ifndef TALLER_TP_EVENT_H
#define TALLER_TP_EVENT_H

#include "event_type.h"
#include "common/events/player.h"
#include "common/events/connection/game_room.h"
#include "../items/bullet.h"
#include "../items/crate.h"
#include "../items/weapon.h"
#include <list>

#define SIN_ASIGNAR 0
class Event {
private:
  EventType type;

public:
  explicit Event(EventType type);

  EventType get_type();

  virtual bool is_connected() const;

  virtual int get_game_code() const;

  virtual int get_position_x() const;
  virtual int get_position_y() const;

  virtual int get_player_id_1() const;
  virtual int get_player_id_2() const;

  virtual std::list<Player> get_players();

  virtual std::list<Bullet> get_bullets();

  virtual std::list<Crate> get_crates();

  virtual std::list<Weapon> get_weapons();

  virtual int get_max_players() const;

    virtual int get_actual_players() const;

    virtual std::list<GameRoom> get_games();
  virtual ~Event() = default;
};

#endif // TALLER_TP_EVENT_H
