#include "game_map.h"
#include "common/events/player.h"
#include "duck.h"
#include <stdexcept>
#include <yaml-cpp/yaml.h>

#define HEIGHT 500
#define WIDTH 500

GameMap::GameMap() {
  readMap("maps/map.yaml");
}

void GameMap::addPlayer(Duck *player) { players.push_back(player); }

Duck *GameMap::findPlayer(int playerId) {
  for (auto player : players) {
    if (player->getId() == playerId) {
      return player;
    }
  }
  return nullptr;
}

void GameMap::update() {
  for (auto player : players) {
    player->update();
  }
}

bool GameMap::checkCollisionsWithBorders(int playerId) {
  Duck *player = findPlayer(playerId);
  if (!player)
    return true;

  if (player->getPositionX() >= width || player->getPositionX() <= 0) {
    return true;
  }
  if (player->getPositionY() >= height || player->getPositionY() <= 0) {
    return true;
  }
  return false;
}

Player GameMap::getPlayerState(int playerId) {
  Duck *duck = findPlayer(playerId);
  if (duck == nullptr) {
    throw std::runtime_error("Jugador no encontrado");
  }

  int id = duck->getId();
  int posX = duck->getPositionX();
  int posY = duck->getPositionY();
  bool dir = duck->getDirection();
  State state = duck->getState();

  Player player(id, posX, posY, dir, state);
  return player;
}

void GameMap::reapDead() {
  for (auto player : players) {
    if (player->getState() == State::DEAD) {
      delete player; 
    }
  }
}

void GameMap::readMap(const std::string &mapPath) {
  cleanMap();

  YAML::Node map = YAML::LoadFile(mapPath);

  height = map["alto"].as<int>();
  width = map["ancho"].as<int>();
  background = map["fondo"].as<std::string>();

  for (auto spawn : map["Spawns"]) {
    spawns.push_back({spawn["x"].as<int>(), spawn["y"].as<int>()});
  }

  for (auto interactuable : map["Interactuables"]) {
    if (interactuable["ID"].as<int>() == 2){
      helmets.push_back({interactuable["x"].as<int>(), interactuable["y"].as<int>()});
  }else if (interactuable["ID"].as<int>() == 1){
        armors.push_back({interactuable["x"].as<int>(), interactuable["y"].as<int>()});
    }else{
        boxes.push_back({interactuable["x"].as<int>(), interactuable["y"].as<int>()});
    }
    }   

    
  for (auto structure : map["tiles"]) {
    int id = structure["tile"].as<int>();
    int nivel_tile = id /8;
    int idTruncado =id - nivel_tile*8;
    std::set<int> nivelesPermitidos = {2, 6,10};
    std::set<int> nivelesSinRampas = {1,3, 5,7, 9,11};

    if (idTruncado >= 6 || 
        (idTruncado >= 4 && idTruncado <= 5 && nivelesPermitidos.count(nivel_tile) > 0)) {
      if (idTruncado==7 || idTruncado==5){
        if (nivelesPermitidos.count(nivel_tile) > 0){
          rightRamps.push_back(Ramp{structure["start_x"].as<int>(), 
                        structure["end_x"].as<int>(), 
                        structure["y"].as<int>(), 
                        id, 0});
        }else{
            leftRamps.push_back(Ramp{structure["start_x"].as<int>(), 
                            structure["end_x"].as<int>(), 
                            structure["y"].as<int>(), 
                            id, 1});
        }
      }else{
        if (nivelesPermitidos.count(nivel_tile) > 0){
          leftRamps.push_back(Ramp{structure["start_x"].as<int>(), 
                        structure["end_x"].as<int>(), 
                        structure["y"].as<int>(), 
                        id, 0});
      }else{
          rightRamps.push_back(Ramp{structure["start_x"].as<int>(), 
                          structure["end_x"].as<int>(), 
                          structure["y"].as<int>(), 
                          id, 1});
      }
      }
    }else{
        structures.push_back({structure["start_x"].as<int>(), 
                        structure["end_x"].as<int>(), 
                        structure["y"].as<int>(), 
                        id});
    }
  }
}

void GameMap::cleanMap() {
  structures.clear();
  leftRamps.clear();
  rightRamps.clear();
  spawns.clear();
  helmets.clear();
  armors.clear();
  boxes.clear();
  height = 0;
  width = 0;
}


GameMap::~GameMap()
{
  for (auto player : players) {
    delete player; 
  }
}

