#ifndef THROWABLE_H
#define THROWABLE_H

#include "common/events/items/weapon_macros.h"
#include "common/events/items/bullet_dto.h"

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
  enum BulletId id;
  bool collidable ;

  
public:
    Throwable(GameMap &map,bool isRight,int pos_x,int pos_y,int reach,BulletId id,bool collidable);
    virtual ~Throwable() = default;
    virtual void update()=0;
    int getPosX() const { return pos_x; }
    int getPosY() const { return pos_y; }
    BulletId getId() const { return id; }
    bool isCollidable() const { return collidable; }

    virtual bool isOver() const=0;
    virtual void consume()=0;

    virtual BulletDTO toDTO() const=0;
};




#endif // THROWABLE_H