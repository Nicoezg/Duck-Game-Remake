#include "maploader.h"
#include <yaml-cpp/yaml.h>
#include <filesystem>
#include <iostream>


#define PATH "../server/logic/maps/"

MapLoader::MapLoader() {

    for (const auto & entry : std::filesystem::directory_iterator(PATH)) {
        maps_paths.push_back(entry.path());
    }
    std::cout << "cargue los mapas" << std::endl;
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

  for (auto spawn : map["Spawns"]) {
    mapa.spawns.push_back({spawn["x"].as<int>(), spawn["y"].as<int>()});
  }

  for (auto interactuable : map["Interactuables"]) {
    if (interactuable["ID"].as<int>() == 2){
      mapa.helmets.push_back({interactuable["x"].as<int>(), interactuable["y"].as<int>()});
  }else if (interactuable["ID"].as<int>() == 1){
        mapa.armors.push_back({interactuable["x"].as<int>(), interactuable["y"].as<int>()});
    }else{
        mapa.boxes.push_back(Box{1, interactuable["x"].as<int>(), interactuable["y"].as<int>()});// vida de la caja 1?
    }
    }   

    
  for (auto structure : map["Structures"]) {
    int id = structure["tile"].as<int>();
    int nivel_tile = id /8;
    int idTruncado =id - nivel_tile*8;
    std::set<int> nivelesPermitidos = {2, 6,10};
    std::set<int> nivelesSinRampas = {1,3, 5,7, 9,11};

    if (idTruncado >= 6 || 
        (idTruncado >= 4 && idTruncado <= 5 && nivelesPermitidos.count(nivel_tile) > 0)) {
      if (idTruncado==7 || idTruncado==5){
        if (nivelesPermitidos.count(nivel_tile) > 0){
          mapa.rightRamps.push_back(Ramp{structure["start_x"].as<int>(), 
                        structure["end_x"].as<int>(), 
                        structure["y"].as<int>(), 
                        id, 0});
        }else{
            mapa.leftRamps.push_back(Ramp{structure["start_x"].as<int>(), 
                            structure["end_x"].as<int>(), 
                            structure["y"].as<int>(), 
                            id, 1});
        }
      }else{
        if (nivelesPermitidos.count(nivel_tile) > 0){
          mapa.leftRamps.push_back(Ramp{structure["start_x"].as<int>(), 
                        structure["end_x"].as<int>(), 
                        structure["y"].as<int>(), 
                        id, 0});
      }else{
          mapa.rightRamps.push_back(Ramp{structure["start_x"].as<int>(), 
                          structure["end_x"].as<int>(), 
                          structure["y"].as<int>(), 
                          id, 1});
      }
      }
    }else{
        mapa.structures.push_back({structure["start_x"].as<int>(), 
                        structure["end_x"].as<int>(), 
                        structure["y"].as<int>(), 
                        id});
    }
  }
    maps.push_back(mapa);
      lastMapIndex++;
    std::cout << "consegui el mapa para la logica" << std::endl;
    std::cout << mapa.background << std::endl;
    std::cout << mapa.structures.size() << std::endl;
    return mapa;
}

Map MapLoader::getactualMap() {

  return maps[lastMapIndex-1];
}

MapDTO MapLoader::getNextMapDTO() {
  Map mapa = getactualMap();
  std::cout << mapa.background << std::endl;
  std::cout << mapa.structures.size() << std::endl;
  std::list<Tile> tiles;
  for (auto structure : mapa.structures) {
    std::cout << "entrando" << std::endl;
    for (int i = structure.start_x; i <= structure.end_x; i++) {
      std::cout << "entrando" << std::endl;
      tiles.push_back({i, i, structure.y, structure.id});
    }
  }
  for (auto ramp : mapa.leftRamps) {
    for (int i = ramp.start_x; i <= ramp.end_x; i++) {
      tiles.push_back({i, i, ramp.y, ramp.id});
    }
  }
  for (auto ramp : mapa.rightRamps) {
    for (int i = ramp.start_x; i <= ramp.end_x; i++) {
      tiles.push_back({i, i, ramp.y, ramp.id});
    }
  }
  int background = (mapa.background == "Forest") ? 0 : 1;
  std::cout << "cargo el DTO con tamaño: "  << tiles.size() << std::endl;
  return MapDTO(std::move(tiles), background, mapa.width, mapa.height);
}
