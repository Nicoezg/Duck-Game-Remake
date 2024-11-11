#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "common/events/player.h"
#include "duck.h"
#include <vector>

class GameMap {
public:
  GameMap(int &height, int &width);

  void addPlayer(Duck *player);
  Duck *findPlayer(int playerId);
  void update();
  bool checkCollisionsWithBorders(int playerId);
  Player getPlayerState(int playerId);

  void reapDead();

private:
  int height;
  int width;
  std::vector<Duck *> players;
};

#endif
