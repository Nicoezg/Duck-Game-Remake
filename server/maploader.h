#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <vector>
#include <string>
#include "structure.h"
#include "logic/box.h"
#include "common/events/map.h"


#define HELMENT_ID 2

#define ARMOR_ID 1

// En Map.h
struct Map {
    std::vector<Structure> structures;  // Plataformas
    std::vector<Ramp> leftRamps;        // Rampas izquierdas
    std::vector<Ramp> rightRamps;       // Rampas derechas
    std::vector<Spawn> spawns;          // Spawns
    std::vector<Helmet> helmets;
    std::vector<Armor> armors;
    std::vector<Box> boxes;
    std::string background;
    int height;
    int width;

   
    int getGroundLevel() const {
        int groundLevel = height; 
       
        for (const auto& structure : structures) {
            if (structure.y < groundLevel) {
                groundLevel = structure.y;
            }
        }
        for (const auto& ramp : leftRamps) {
            if (ramp.y < groundLevel) {
                groundLevel = ramp.y;
            }
        }
        for (const auto& ramp : rightRamps) {
            if (ramp.y < groundLevel) {
                groundLevel = ramp.y;
            }
        }
        return groundLevel;
    }
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