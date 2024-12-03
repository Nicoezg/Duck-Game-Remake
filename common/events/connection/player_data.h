//
// Created by fran on 24/11/24.
//

#ifndef TALLER_TP_PLAYER_DATA_H
#define TALLER_TP_PLAYER_DATA_H

#include <string>

class PlayerData {
private:
  int id;
  std::string name;

public:
  PlayerData(int id, std::string name);

  int get_id() const;

  const std::string &get_name() const;
};

#endif // TALLER_TP_PLAYER_DATA_H
