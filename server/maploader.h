#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <vector>
#include <string>
#include "structure.h"
#include "logic/box.h"
#include "common/events/map.h"



struct Map{
    std::vector<Structure> structures;
    std::vector<Ramp> leftRamps;
    std::vector<Ramp> rightRamps;
    std::vector<Spawn> spawns; 
    std::vector<Helmet> helmets;
    std::vector<Armor> armors;
    std::vector<Box> boxes;
    std::string background;
    int height;
    int width;
};
class MapLoader{
    private:
        std::vector<std::string> maps_paths;
        std::vector<Map> maps;
        size_t lastMapIndex;
    public:
        MapLoader();
        ~MapLoader();

        Map getNextMap();
        Map getactualMap();
        MapDTO getNextMapDTO();
};


#endif // MAPLOADER_H