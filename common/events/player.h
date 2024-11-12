//
// Created by fran on 24/10/24.
//

#ifndef TALLER_TP_PLAYER_H
#define TALLER_TP_PLAYER_H

#include "player_macros.h"
#include <string>

class Player {
private:
  int player_id;
  int position_x;
  int position_y;
  bool right;
  enum State state;

public:
  Player(int player_id, int position_x, int position_y, bool right,
         State state);

  int get_player_id() const;

  int get_position_x() const;

  int get_position_y() const;

  std::string get_text() const;

  State get_state() const;

  bool is_right() const;
};

#endif // TALLER_TP_PLAYER_H
