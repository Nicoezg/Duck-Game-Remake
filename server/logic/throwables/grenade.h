#ifndef GRENADE_H
#define GRENADE_H

#include "throwable.h"

class Grenade : public Throwable {
private:      
  int framesToExplode; 

public:
  Grenade(GameMap &map,bool isRight,int pos_x,int pos_y):Throwable(map,isRight,pos_x,pos_y,5) ,  framesToExplode(160) {
  }
  void update() override;
  
};

#endif // GRENADE_H
