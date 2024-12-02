#include "maploader.h"
#include <filesystem>
#include <iostream>
#include <algorithm> 
#include <yaml-cpp/yaml.h>

#define PATH "../server/logic/maps/"

MapLoader::MapLoader() {
  // cppcheck-suppress useStlAlgorithm
  for (const auto &entry : std::filesystem::directory_iterator(PATH)) {
    maps_paths.push_back(entry.path());
  }
  lastMapIndex = 0;
}

MapLoader::~MapLoader() {}

Map MapLoader::getNextMap() {
  Map mapa;
  if (lastMapIndex > maps_paths.size() - 1) {
    lastMapIndex = 0;
    mapa = logicMaps[lastMapIndex];
    lastMapIndex++;
    return mapa;
  }
    if (maps.size() == maps_paths.size()) {
        lastMapIndex++;
        return logicMaps[lastMapIndex-1];
    }

 YAML::Node map = YAML::LoadFile(maps_paths[lastMapIndex]);

    if (map["Spawns"].size()==0) {
        maps_paths.erase(maps_paths.begin() + lastMapIndex);
        return getNextMap();
    }      

  mapa.height = map["alto"].as<int>();
  mapa.width = map["ancho"].as<int>();
  mapa.background = map["fondo"].as<std::string>();

  for (auto spawn : map["Spawns"]) {
    mapa.spawns.emplace_back(spawn["x"].as<int>(), spawn["y"].as<int>());
  }

  for (auto interactuable : map["Interactuables"]) {
    switch (interactuable["ID"].as<int>()) {
    case HELMENT_ID:
      mapa.helmets.emplace_back(interactuable["x"].as<int>(),
                                interactuable["y"].as<int>());
      break;
    case ARMOR_ID:
      mapa.armors.emplace_back(interactuable["x"].as<int>(),
                               interactuable["y"].as<int>());
      break;
    case WEAPON_ID:
      mapa.weaponSpawns.emplace_back(interactuable["x"].as<int>(),
                                     interactuable["y"].as<int>());
      break;
    case BOX_ID:
      mapa.boxes.emplace_back(4, interactuable["x"].as<int>(),
                              interactuable["y"].as<int>());
      break;
    }
  }
  for (auto structure : map["Structures"]) {
    mapa.structures.emplace_back(
        structure["start_x"].as<int>(), structure["end_x"].as<int>(),
        structure["start_y"].as<int>(), structure["end_y"].as<int>(),
        structure["tile"].as<int>());
  }

  lastMapIndex++;
  maps.push_back(mapa);

  Map logicMap;
  logicMap.height = mapa.height;
  logicMap.width = mapa.width;
  logicMap.background = mapa.background;

  // Fusionar estructuras adyacentes
  std::vector<Structure> mergedStructures = mapa.structures;

  // Ordenar por coordenadas para facilitar la fusión
  std::sort(mergedStructures.begin(), mergedStructures.end(),
            [](const Structure &a, const Structure &b) {
              if (a.start_y == b.start_y)
                return a.start_x < b.start_x;
              return a.start_y < b.start_y;
            });

  // Fusión de estructuras adyacentes
  std::vector<Structure> fusedStructures;
  for (const auto &structure : mergedStructures) {
    if (fusedStructures.empty()) {
      fusedStructures.push_back(structure);
    } else {
      auto &last = fusedStructures.back();
      // Verificar si son adyacentes horizontal o verticalmente
      if ((last.end_x + 1 == structure.start_x &&
           last.start_y == structure.start_y &&
           last.end_y == structure.end_y) ||
          (last.end_y + 1 == structure.start_y &&
           last.start_x == structure.start_x &&
           last.end_x == structure.end_x)) {
        // Fusionar estructuras
        last.end_x = std::max(last.end_x, structure.end_x);
        last.end_y = std::max(last.end_y, structure.end_y);
      } else {
        fusedStructures.push_back(structure);
      }
    }
  }


    std::cout<<"Procese"<<std::endl;
  // Guardar las estructuras fusionadas en el mapa lógico
  logicMap.structures = std::move(fusedStructures);

  // Copiar los demás elementos al mapa lógico
  for (auto spawn : mapa.spawns) {
    logicMap.spawns.emplace_back(spawn.x, spawn.y);
  }
  for (auto helmet : mapa.helmets) {
    logicMap.helmets.emplace_back(helmet.x, helmet.y);
  }
  for (auto armor : mapa.armors) {
    logicMap.armors.emplace_back(armor.x, armor.y);
  }
  for (auto weapon : mapa.weaponSpawns) {
    logicMap.weaponSpawns.emplace_back(weapon.x, weapon.y);
  }
  for (auto box : mapa.boxes) {
    logicMap.boxes.emplace_back(box.get_hp(), box.get_posx(), box.get_posy());
  }

  // Guardar el mapa lógico
  logicMaps.push_back(logicMap);

  return logicMap;
}

Map MapLoader::getactualMap() { return maps[lastMapIndex - 1]; }

MapDTO
MapLoader::getNextMapDTO() { // en realidad devuelve al actual, pero hay que
                             // llamar antes a get next map asi actualiza map
  Map mapa = getactualMap();
  std::list<Tile> tiles;
  // cppcheck-suppress useStlAlgorithm
  for (auto structure : mapa.structures) {
    tiles.push_back({structure.start_x, structure.end_x, structure.start_y,
                     structure.end_y, structure.id});
  }
  int background;
  if (mapa.background == "Forest") {
    background = 0;
  } else if (mapa.background == "Lava") {
    background = 1;
  } else {
    background = 2;
  }
  return MapDTO(std::move(tiles), background, mapa.width, mapa.height);
}
