#include "banana.h"
#include "server/configs/configurations.h" 
#include "server/logic/duck.h"


ThrownBanana::ThrownBanana(GameMap &map, bool isRight, int pos_x, int pos_y,
                           bool aimingUp)
    : Throwable(map, isRight, pos_x, pos_y, 150,THROWN_BANANA_V2,false,aimingUp) {}

void ThrownBanana::update() {
    if (!aimingUp &&distance_travelled < reach && !onGround) {
        if (isRight) {
            pos_x += 3;
        } else {
            pos_x -= 2;
    }
    }
    
    distance_travelled+=2;
    if (!onGround) {
        pos_y += CONFIG.getDuckConfig().getGravity();
    }

    hitBox bananaBox = {pos_x, pos_y, 8, 8};

    for (auto structure : map.getMap().structures) {
        hitBox structureBox = {structure.start_x * 16, structure.start_y * 16,
                               (structure.end_x + 1 - structure.start_x) * 16, (structure.end_y+1 - structure.start_y) * 16};
        if (hitBox::isColliding(bananaBox, structureBox)) {
            pos_y = structure.start_y * 16 - 16;
            onGround = true;
            collidable = true;
        }

    }

}    



ThrowableDTO ThrownBanana::toDTO() const {
  return {pos_x, pos_y, THROWN_BANANA_V2, 0, isRight,consumed};
}