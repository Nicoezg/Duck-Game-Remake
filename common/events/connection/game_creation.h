#ifndef TALLER_TP_GAME_CREATION_H
#define TALLER_TP_GAME_CREATION_H

#include "common/events/base/event.h"

class GameCreation : public Event {
private:
  int game_code;
  int player_id_1;
  int player_id_2;

  int actual_players;
  int max_players;

public:
  GameCreation(int game_code, int player_id_1, int player_id_2, int actual_players, int max_players);

  int get_game_code() const override;

  int get_player_id_1() const override;

  int get_player_id_2() const override;

  bool is_connected() const override;

  int get_max_players() const override;

  int get_actual_players() const override;
};

#endif // TALLER_TP_GAME_CREATION_H
