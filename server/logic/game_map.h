#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "common/events/player.h"
#include <vector>
#include "structure.h"
#include <string>
#include "server/maploader.h"

class Duck;

class GameMap {
private:
    std::vector<Duck *> players;
    MapLoader mapLoader;
    Map map;

public:
  GameMap();

  void addPlayer(Duck *player);
  Duck *findPlayer(int playerId);
  void update();
  bool checkCollisionsWithBorders(int playerId);
  Player getPlayerState(int playerId);

  void reapDead();

  ~GameMap();
};

#endif
