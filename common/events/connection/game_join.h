//
// Created by fran on 21/10/24.
//

#ifndef TALLER_TP_GAME_JOIN_H
#define TALLER_TP_GAME_JOIN_H

#include "common/events/base/event.h"

class GameJoin : public Event {
private:
  int player_id_1;
  int player_id_2;

  bool connected;

  int actual_players;
  int max_players;

public:
  GameJoin(int player_id_1, int player_id_2, bool connected, int actual, int max);

  int get_player_id_1() const override;

  int get_player_id_2() const override;

  int get_game_code() const override;

  bool is_connected() const override;

    int get_max_players() const override;

    int get_actual_players() const override;
};

#endif // TALLER_TP_GAME_JOIN_H
