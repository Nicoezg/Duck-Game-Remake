//
// Created by fran on 21/10/24.
//

#ifndef TALLER_TP_EVENT_H
#define TALLER_TP_EVENT_H

#include "event_type.h"
#include "player.h"
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

  virtual ~Event() = default;
};

#endif // TALLER_TP_EVENT_H
