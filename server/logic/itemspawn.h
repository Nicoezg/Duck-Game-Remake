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
        bool wasInBox;

    public:
     
        ItemSpawn(int pos_x , int pos_y, ItemSpawnId content, bool wasInBox);
        int getRespawnTime() const;
        int getPosX() const;
        int getPosY() const;
        bool isAvailable() const;
        void update();
        ItemSpawnId getContent() const;
        ItemSpawnDTO toDTO() const;
       

        void notAvailable();

        ~ItemSpawn();

};  

#endif // ITEM_SPAWN_H