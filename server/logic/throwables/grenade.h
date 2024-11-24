#ifndef GRENADE_H
#define GRENADE_H

#include "throwable.h"

class ThrownGrenade : public Throwable {
private:      
  int framesToExplode; 
  bool ownerHasGrenade;

public:
  ThrownGrenade(GameMap &map,bool isRight,int pos_x,int pos_y,int framesToexplode):Throwable(map,isRight,pos_x,pos_y,5) , framesToExplode(framesToexplode) {
  }
  void update() override;

  BulletDTO toDTO() const override {
    return {pos_x, pos_y, THROWN_GRENADE, 0, isRight};
  }

  bool isOver() const override { return framesToExplode == 0; }
  
};

#endif // GRENADE_H
