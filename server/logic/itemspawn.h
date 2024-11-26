#ifndef ITEM_SPAWN_H
#define ITEM_SPAWN_H

#include "common/events/items/item_spawn.h"

class ItemSpawn {
    private: 
        int pos_x;
        int pos_y;
        ItemSpawnId content;

    public:
        ItemSpawn(int pos_x , int pos_y, ItemSpawnId content);
        int getPosX() const;
        int getPosY() const;
        ItemSpawnId getContent() const;

        ~ItemSpawn();

};  

#endif // ITEM_SPAWN_H