#include "grenade.h"
#include "server/logic/explosion.h"
#include <iostream>
#include "server/logic/duck.h"


void ThrownGrenade::update() {
  if (framesToExplode<150){
    startThrow = false;
  }
  framesToExplode--;
  if (isRight) {
    pos_x += 1;
  } else {
    pos_x -= 1;
  }
  pos_y += 1;
  hitBox grenadeBox = {pos_x, pos_y, 8, 8};
  for (auto structure: map.getMap().structures) {
    hitBox structureBox = {structure.start_x * 16, structure.y * 16,
                           (structure.end_x + 1 - structure.start_x) * 16, 16};
    if (hitBox::isColliding(grenadeBox, structureBox)) {
      pos_y = structure.y * 16 - 8;
    }
  } 
    if (framesToExplode == 0) {
    consume();
  }
}

void ThrownGrenade::consume() {
  map.addExplosion(std::make_unique<Explosion>(map,pos_x, pos_y));
}

ThrowableDTO ThrownGrenade::toDTO() const {
  return {pos_x, pos_y, THROWN_GRENADE_V2, 0, isRight,startThrow};
}


