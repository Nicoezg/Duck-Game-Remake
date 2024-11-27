#ifndef THROWABLE_H
#define THROWABLE_H

#include "common/events/items/weapon_macros.h"
#include "common/events/items/throwable_macros.h"
#include "common/events/items/throwable_dto.h"

#define CONFIG Configurations::configurations()

class GameMap;
class Duck;



class Throwable {
protected:
  GameMap &map;
  bool isRight;
  int pos_x;
  int pos_y;
  int reach;
  enum ThrowableId id;
  bool collidable ;
  bool aimingUp;

  
public:
    Throwable(GameMap &map,bool isRight,int pos_x,int pos_y,int reach,ThrowableId id,bool collidable,bool aimingUp);
    virtual ~Throwable() = default;
    virtual void update()=0;
    int getPosX() const { return pos_x; }
    int getPosY() const { return pos_y; }
    ThrowableId getId() const { return id; }
    bool isCollidable() const { return collidable; }

    virtual bool isOver() const=0;
    virtual void consume()=0;

    virtual ThrowableDTO toDTO() const=0;
};




#endif // THROWABLE_H