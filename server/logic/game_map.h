#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "common/events/player.h"
#include <vector>
#include "structure.h"
#include <string>

class Duck;

class GameMap {
private:
    std::vector<Duck *> players;
    std::vector<Structure> structures;
    std::vector<Ramp> leftRamps;
    std::vector<Ramp> rightRamps;
    std::vector<Spawn> spawns; 
    std::vector<Helmet> helmets;
    std::vector<Armor> armors;
    std::vector<Box> boxes;
    std::string background;
    int height;
    int width;

    void readMap(const std::string &mapPath);
    void cleanMap();


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
