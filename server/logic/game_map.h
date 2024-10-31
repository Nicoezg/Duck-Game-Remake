#include "duck.h"
#include <vector>
#ifndef GAME_MAP_H
#define GAME_MAP_H

class GameMap {
    private:
        int height;
        int width;
        std::vector<Duck*> players;
    
    public:
        GameMap(int& height, int& width);
        void addPlayer(Duck *player);
        void update();
        bool checkCollisionsWithBorders(int playerId);
        

};

#endif // GAME_MAP_H
    