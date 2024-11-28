#ifndef GRENADE_THROWABLE_H
#define GRENADE_THROWABLE_H

#include "throwable.h"

class ThrownGrenade : public Throwable {
private:      
  int framesToExplode; 
  bool ownerHasGrenade;
  float angle;
  bool startThrow;

public:
  ThrownGrenade(GameMap &map,bool isRight,int pos_x,int pos_y,int framesToexplode,bool aimingUp):Throwable(map,isRight,pos_x,pos_y,5,THROWN_GRENADE_V2,false,aimingUp) , 
  framesToExplode(framesToexplode),angle(0) {
    startThrow = true;
  }
  void update() override;

  ThrowableDTO toDTO() const override;

  bool isOver() const override { return framesToExplode == 0; }

  void consume() override ;
  
};

#endif // GRENADE_THROWABLE_H
