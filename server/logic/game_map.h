#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "common/events/player.h"
#include <vector>

class Duck;

class GameMap {
private:
  std::vector<Duck *> players;

public:
  GameMap();

  void addPlayer(Duck *player);
  Duck *findPlayer(int playerId);
  void update();
  bool checkCollisionsWithBorders(int playerId);
  Player getPlayerState(int playerId);

  void reapDead();
};

#endif
