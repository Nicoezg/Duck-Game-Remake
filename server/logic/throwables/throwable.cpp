#include "throwable.h"
#include "server/logic/duck.h"
#include "server/logic/game_map.h"
#include <iostream>

Throwable::Throwable(GameMap &map, bool isRight, int pos_x, int pos_y,int reach)
    : map(map), isRight(isRight), pos_x(pos_x), pos_y(pos_y),reach(reach) {}