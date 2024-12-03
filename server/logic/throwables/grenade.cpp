#include "grenade.h"
#include "server/logic/duck.h"
#include "server/logic/explosion.h"
#include <iostream>

void ThrownGrenade::update() {
  if (framesRemaining < framesToExplode) {
    startThrow = false;
  }
  framesRemaining--;
  if (!aimingUp && distance_travelled / TILE_LENGTH < reach) {
    if (isRight) {
      pos_x += 1;
      angle += 5;
    } else {
      pos_x -= 1;
      angle -= 5;
    }
    distance_travelled += 1;
  }
  pos_y += CONFIG.getDuckConfig().getGravity();
  hitBox grenadeBox = hitBox(pos_x, pos_y, 8, 8);
  for (auto structure : map.getMap().structures) {
    hitBox structureBox =
        hitBox(structure.start_x * TILE_LENGTH, structure.start_y * TILE_LENGTH,
               (structure.end_x + 1 - structure.start_x) * TILE_LENGTH,
               (structure.end_y + 1 - structure.start_y) * TILE_LENGTH);
    if (hitBox::isColliding(grenadeBox, structureBox)) {
      pos_y = structure.start_y * TILE_LENGTH - 8;
    }
  }
  if (framesRemaining == 0) {
    consume();
  }
}

void ThrownGrenade::consume() {
  map.addExplosion(std::make_unique<Explosion>(map, pos_x, pos_y));
}

ThrowableDTO ThrownGrenade::toDTO() const {
  return {pos_x, pos_y, THROWN_GRENADE, angle, isRight, startThrow};
}
