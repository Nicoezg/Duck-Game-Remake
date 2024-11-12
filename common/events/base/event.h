//
// Created by fran on 21/10/24.
//

#ifndef TALLER_TP_EVENT_H
#define TALLER_TP_EVENT_H

#include "event_type.h"
#include "common/events/player.h"
#include "common/events/connection/game_room.h"
#include "../tile.h"
#include "../items/bullet.h"
#include "../items/crate.h"
#include "../items/weapon.h"
#include <list>
#include <vector>

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

  virtual std::list<Player> get_players() const;

  virtual std::list<Bullet> get_bullets() const;

  virtual std::list<Crate> get_crates() const;

  virtual std::list<Weapon> get_weapons() const;

  virtual int get_max_players() const;

  virtual int get_actual_players() const;

  virtual std::list<GameRoom> get_games();

  virtual std::vector<Tile> get_platforms() const;

  virtual int get_background_id() const;

  virtual int get_width() const;

  virtual int get_length() const;

  virtual ~Event() = default;
};

#endif // TALLER_TP_EVENT_H
