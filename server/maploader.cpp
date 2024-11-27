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
        return maps[lastMapIndex];
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
        int nivel_tile = id / 8;
        int idTruncado = id - nivel_tile * 8;
        std::set<int> nivelesPermitidos = {2, 6, 10};
        std::set<int> nivelesSinRampas = {1, 3, 5, 7, 9, 11};

        if (idTruncado >= 6 ||
            (idTruncado >= 4 && idTruncado <= 5 && nivelesPermitidos.count(nivel_tile) > 0)) {
            if (idTruncado == 7 || idTruncado == 5) {
                if (nivelesPermitidos.count(nivel_tile) > 0) {
                    mapa.rightRamps.emplace_back(structure["start_x"].as<int>(),
                                                   structure["end_x"].as<int>(),
                                                   structure["y"].as<int>(),
                                                   id, 0);
                } else {
                    mapa.leftRamps.emplace_back(structure["start_x"].as<int>(),
                                                  structure["end_x"].as<int>(),
                                                  structure["y"].as<int>(),
                                                  id, 1);
                }
            } else {
                if (nivelesPermitidos.count(nivel_tile) > 0) {
                    mapa.leftRamps.emplace_back(structure["start_x"].as<int>(),
                                                  structure["end_x"].as<int>(),
                                                  structure["y"].as<int>(),
                                                  id, 0);
                } else {
                    mapa.rightRamps.emplace_back(structure["start_x"].as<int>(),
                                                   structure["end_x"].as<int>(),
                                                   structure["y"].as<int>(),
                                                   id, 1);
                }
            }
        } else {
            mapa.structures.emplace_back(structure["start_x"].as<int>(),
                                       structure["end_x"].as<int>(),
                                       structure["y"].as<int>(),
                                       id);
        }
    }
    maps.push_back(mapa);
    lastMapIndex++;

    std::cout << mapa.background << std::endl;
    std::cout << mapa.structures.size() << std::endl;
    return mapa;
}

Map MapLoader::getactualMap() {

    return maps[lastMapIndex - 1];
}

MapDTO MapLoader::getNextMapDTO() {//en realidad devuelve al actual, pero hay que llamar antes a get next map asi actualiza map
    Map mapa = getactualMap();
    std::cout << mapa.background << std::endl;
    std::cout << mapa.structures.size() << std::endl;
    std::list<Tile> tiles;
    for (auto structure: mapa.structures) {
        tiles.push_back({structure.start_x, structure.end_x, structure.y, structure.id});
    }
    for (auto ramp: mapa.leftRamps) {
        tiles.push_back({ramp.start_x, ramp.end_x, ramp.y, ramp.id});
    }
    for (auto ramp: mapa.rightRamps) {
        tiles.push_back({ramp.start_x, ramp.end_x, ramp.y, ramp.id});
    }
    int background = (mapa.background == "Forest") ? 0 : 1;
    return MapDTO(std::move(tiles), background, mapa.width, mapa.height);
}
