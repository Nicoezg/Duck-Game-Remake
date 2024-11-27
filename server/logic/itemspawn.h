#ifndef ITEM_SPAWN_H
#define ITEM_SPAWN_H

#include "common/events/items/item_spawn.h"

class ItemSpawn {
    private: 
        int pos_x;
        int pos_y;
        ItemSpawnId content;
        bool available;     
        int respawnTime;

    public:
     
        ItemSpawn(int pos_x , int pos_y, ItemSpawnId content);
        int getRespawnTime() const;
        int getPosX() const;
        int getPosY() const;
        bool isAvailable() const;
        ItemSpawnId getContent() const;
        ItemSpawnDTO toDTO() const;
       

        void notAvailable();

        ~ItemSpawn();

};  

#endif // ITEM_SPAWN_H