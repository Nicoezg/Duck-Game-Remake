#include "maploader.h"
#include <yaml-cpp/yaml.h>
#include <filesystem>


#define PATH "../maps/"

MapLoader::MapLoader() {

    for (const auto & entry : std::filesystem::directory_iterator(PATH)) {
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
  lastMapIndex++;  
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
    return mapa;
}
