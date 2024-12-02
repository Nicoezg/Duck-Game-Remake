#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "server/logic/duck.h"
#include "server/logic/game_map.h"
#include <vector>
class Explosion {
private:
  GameMap &map;
  int posX;
  int posY;
  int radius;
  int framesRemaining;
  std::vector<Duck *> playersDamaged;

public:
  Explosion(GameMap &map, int posX, int posY);

  std::vector<Duck *> &getPlayersDamaged() { return playersDamaged; }

  void addPlayerDamaged(Duck *player) { playersDamaged.push_back(player); }

  void update();

  bool isOver() const { return framesRemaining == 0; }

  int getPosX() const { return posX; }

  int getPosY() const { return posY; }

  int getRadius() const { return radius; }

  ExplosionDTO toDTO() const {
    return ExplosionDTO(posX, posY, framesRemaining);
  }
};

#endif // EXPLOSION_H