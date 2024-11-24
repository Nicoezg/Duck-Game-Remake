#include "explosion.h"

Explosion::Explosion(GameMap &map,int x, int y)
    : map(map),posX(x), posY(y),radius(16), framesRemaining(48) {}

void Explosion::update() {
    framesRemaining--;
    if (framesRemaining == 0) {
        //destruirse
    }
}