#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <vector>
#include <string>
#include "structure.h"
#include "logic/box.h"
#include "common/events/map.h"


#define HELMENT_ID 3
#define ARMOR_ID 2
#define BOX_ID 1
#define WEAPON_ID 0

// En Map.h
struct Map {
    std::vector<Structure> structures;  // Plataformas    
    std::vector<Spawn> spawns;          
    std::vector<Helmet> helmets;
    std::vector<Armor> armors;
    std::vector<WeaponSpawn> weaponSpawns;
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