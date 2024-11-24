#include "grenade.h"
#include "server/logic/duck.h"
#include "server/logic/explosion.h"



void ThrownGrenade::update() {
  framesToExplode--;
  if (isRight) {
    pos_x += 1;
  } else {
    pos_x -= 1;
  }
  if (pos_y < map.getMap().getGroundLevel() * 16) {
    pos_y += 1;
  }

  if (framesToExplode == 0) {
    map.addExplosion(std::make_unique<Explosion>(map,pos_x, pos_y));
  }

  
}



