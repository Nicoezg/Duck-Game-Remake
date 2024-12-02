//
// Created by fran on 04/11/24.
//

#ifndef TALLER_TP_REFRESH_H
#define TALLER_TP_REFRESH_H

#include "common/events/base/event.h"
#include "game_room.h"

class Refresh : public Event {
private:
  std::list<GameRoom> games;

public:
  explicit Refresh(std::list<GameRoom> games);

  std::list<GameRoom> get_games() const override;

  bool is_connected() const override;
};

#endif // TALLER_TP_REFRESH_H
