#include "banana.h"
#include "server/configs/configurations.h" 

ThrownBanana::ThrownBanana(GameMap &map, bool isRight, int pos_x, int pos_y,
                           int reach)
    : Throwable(map, isRight, pos_x, pos_y, reach) {}

void ThrownBanana::update() {
    if (isRight) {
        pos_x += 1;
    } else {
        pos_x -= 1;
    }
    pos_y -= CONFIG.getDuckConfig().getGravity();

}    

BulletDTO ThrownBanana::toDTO() const {
  return {pos_x, pos_y, THROWN_BANANA, 0, isRight};
}