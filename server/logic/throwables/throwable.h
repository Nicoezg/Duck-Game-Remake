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
  
public:
    Throwable(GameMap &map,bool isRight,int pos_x,int pos_y,int reach);
    virtual ~Throwable() = default;
    virtual void update()=0;
    int getPosX() const { return pos_x; }
    int getPosY() const { return pos_y; }

    BulletDTO toDTO() const;
};




#endif // THROWABLE_H