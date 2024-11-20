#include "grenade.h"
#include "server/logic/duck.h"


void Grenade::update() {
  framesToExplode--;
  if (framesToExplode %2){
    if (isRight) {
      pos_x += 1;
    } else {
      pos_x -= 1;
    }
  }
  pos_y-=CONFIG.getGravity();

  if (framesToExplode == 0) {
    
  }

  
}

