#include "maploader.h"
#include <yaml-cpp/yaml.h>
#include <filesystem>
#include <iostream>


#define PATH "../server/logic/maps/"

MapLoader::MapLoader() {

    for (const auto &entry: std::filesystem::directory_iterator(PATH)) {
        maps_paths.push_back(entry.path());
    }
    lastMapIndex = 0;
}

MapLoader::~MapLoader() {}


Map MapLoader::getNextMap() {
    Map mapa;
    if (lastMapIndex > maps_paths.size() - 1) {
        lastMapIndex = 0;
        std::cout << lastMapIndex << std::endl;
        mapa = maps[lastMapIndex];
        lastMapIndex++;
        return mapa;
    }
    YAML::Node map = YAML::LoadFile(maps_paths[lastMapIndex]);

    mapa.height = map["alto"].as<int>();
    mapa.width = map["ancho"].as<int>();
    mapa.background = map["fondo"].as<std::string>();

    for (auto spawn: map["Spawns"]) {
        mapa.spawns.emplace_back(spawn["x"].as<int>(), spawn["y"].as<int>());
    }

    for (auto interactuable: map["Interactuables"]) {
        switch (interactuable["ID"].as<int>()) {
            case HELMENT_ID:
                mapa.helmets.emplace_back(interactuable["x"].as<int>(), interactuable["y"].as<int>());
                break;
            case ARMOR_ID:
                mapa.armors.emplace_back(interactuable["x"].as<int>(), interactuable["y"].as<int>());
                break;
            case WEAPON_ID:
                mapa.weaponSpawns.emplace_back(interactuable["x"].as<int>(), interactuable["y"].as<int>());
                break;
            case BOX_ID:
                mapa.boxes.emplace_back(4,interactuable["x"].as<int>(), interactuable["y"].as<int>());
                break;
        }
    }


    for (auto structure: map["Structures"]) {
        int id = structure["tile"].as<int>();
        mapa.structures.emplace_back(structure["start_x"].as<int>(), structure["end_x"].as<int>(), structure["start_y"].as<int>(),structure["end_y"].as<int>(), id);
    }
    
    lastMapIndex++;
    maps.push_back(mapa);

    Map logicMap;
    logicMap.height = mapa.height;
    logicMap.width = mapa.width;
    logicMap.background = mapa.background;
    for (auto structure: mapa.structures) {
        logicMap.structures.emplace_back(structure.start_x, structure.end_x, structure.start_y, structure.end_y, structure.id);
    }
    for (auto spawn: mapa.spawns) {
        logicMap.spawns.emplace_back(spawn.x, spawn.y);
    }
    for (auto helmet: mapa.helmets) {
        logicMap.helmets.emplace_back(helmet.x, helmet.y);
    }
    for (auto armor: mapa.armors) {
        logicMap.armors.emplace_back(armor.x, armor.y);
    }
    for (auto weapon: mapa.weaponSpawns) {
        logicMap.weaponSpawns.emplace_back(weapon.x, weapon.y);
    }
    for (auto box: mapa.boxes) {
        logicMap.boxes.emplace_back(box.get_hp(), box.get_posx(), box.get_posy());
    }
    logicMaps.push_back(logicMap);

    return logicMap;
}

Map MapLoader::getactualMap() {

    return maps[lastMapIndex - 1];
}

MapDTO MapLoader::getNextMapDTO() {//en realidad devuelve al actual, pero hay que llamar antes a get next map asi actualiza map
    Map mapa = getactualMap();
    std::list<Tile> tiles;
    for (auto structure: mapa.structures) {
        tiles.push_back({structure.start_x, structure.end_x, structure.start_y,structure.end_y, structure.id});
    }
    int background ;
    if (mapa.background == "Forest") {
        background = 0;
    } else if (mapa.background == "Lava") {
        background = 1;
    } else {
        background = 2;
    }
    return MapDTO(std::move(tiles), background, mapa.width, mapa.height);
}
