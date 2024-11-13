#include "game_map.h"
#include "common/events/player.h"
#include "duck.h"
#include <stdexcept>

#define HEIGHT 500
#define WIDTH 500

GameMap::GameMap() = default;

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

  if (player->getPositionX() >= WIDTH || player->getPositionX() <= 0) {
    return true;
  }
  if (player->getPositionY() >= HEIGHT || player->getPositionY() <= 0) {
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

GameMap::~GameMap()
{
  for (auto player : players) {
    delete player; 
  }
}

