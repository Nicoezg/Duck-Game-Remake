#ifndef TALLER_TP_GAME_CREATION_H
#define TALLER_TP_GAME_CREATION_H

#include "common/events/base/event.h"

class GameCreation : public Event {
private:
  GameRoom game_room;
  int player_id_1;
  int player_id_2;
  std::list<PlayerData> players_data;

public:
  GameCreation(GameRoom game_room, int player_id_1, int player_id_2,
               std::list<PlayerData> players_data);

  GameRoom get_game_room() const override;

  int get_player_id_1() const override;

  std::list<PlayerData> get_players_data() const override;

  int get_player_id_2() const override;

  bool is_connected() const override;

  int get_max_players() const override;

  int get_actual_players() const override;
};

#endif // TALLER_TP_GAME_CREATION_H
