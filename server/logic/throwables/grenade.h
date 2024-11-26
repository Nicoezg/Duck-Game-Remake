#ifndef GRENADE_H
#define GRENADE_H

#include "throwable.h"

class ThrownGrenade : public Throwable {
private:      
  int framesToExplode; 
  bool ownerHasGrenade;
  float angle;

public:
  ThrownGrenade(GameMap &map,bool isRight,int pos_x,int pos_y,int framesToexplode):Throwable(map,isRight,pos_x,pos_y,5) , framesToExplode(framesToexplode),angle(0) {
  }
  void update() override;

  BulletDTO toDTO() const override;

  bool isOver() const override { return framesToExplode == 0; }
  
};

#endif // GRENADE_H
