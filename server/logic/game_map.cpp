#include "game_map.h"
#include "common/events/player.h"
#include <stdexcept>

GameMap::GameMap(int &height, int &width) : height(height), width(width) {}

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
      delete player; // ??
    }
  }
}