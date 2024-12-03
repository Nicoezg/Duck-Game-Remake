#include "banana.h"
#include "server/logic/duck.h"

#define REACH CONFIG.getBulletConfig(BANANA_NAME).getReach()

ThrownBanana::ThrownBanana(GameMap &map, bool isRight, int pos_x, int pos_y,
                           bool aimingUp)
    : Throwable(map, isRight, pos_x, pos_y, REACH, THROWN_BANANA, false,
                aimingUp) {}

void ThrownBanana::update() {
  if (!aimingUp && distance_travelled / TILE_LENGTH < reach && !onGround) {
    if (isRight) {
      pos_x += 3;
    } else {
      pos_x -= 3;
    }
  }

  distance_travelled += 3;
  if (!onGround) {
    pos_y += CONFIG.getDuckConfig().getGravity();
  }

  hitBox bananaBox = hitBox(pos_x, pos_y, 8, 8);

  for (auto structure : map.getMap().structures) {
    hitBox structureBox =
        hitBox(structure.start_x * TILE_LENGTH, structure.start_y * TILE_LENGTH,
               (structure.end_x + 1 - structure.start_x) * TILE_LENGTH,
               (structure.end_y + 1 - structure.start_y) * TILE_LENGTH);
    if (hitBox::isColliding(bananaBox, structureBox)) {
      pos_y = structure.start_y * TILE_LENGTH - TILE_LENGTH;
      onGround = true;
      collidable = true;
    }
  }

  


}

ThrowableDTO ThrownBanana::toDTO() const {
  return {pos_x, pos_y, THROWN_BANANA, 0, isRight, consumed};
}