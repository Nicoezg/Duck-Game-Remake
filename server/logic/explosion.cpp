#include "explosion.h"

Explosion::Explosion(GameMap &map,int x, int y)
    : map(map),posX(x), posY(y),radius(64), framesRemaining(48) {}

void Explosion::update() {
    framesRemaining--;
}