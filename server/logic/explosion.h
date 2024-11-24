#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "server/logic/game_map.h"

class Explosion {
    private:
    GameMap &map;
    int posX;
    int posY;
    int radius;
    int framesRemaining;

    public:

    Explosion(GameMap &map,int posX, int posY);

    void update();

    bool isOver() const { return framesRemaining == 0; }    

    ExplosionDTO toDTO() const {
        return ExplosionDTO(posX, posY, framesRemaining);
    }

};

#endif // EXPLOSION_H