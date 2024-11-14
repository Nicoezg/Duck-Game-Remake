
#include "common/events/player.h"
#include "duck.h"
#include <stdexcept>
#include <iostream>
#include "game_map.h"

#define HEIGHT 500
#define WIDTH 500

GameMap::GameMap() = default;

void GameMap::addPlayer(int player_id) {
    // La línea de abajo está de ejemplo, no compila y no funciona realmente así.
    // Hay que obtener las cosas me parece

    /*Weapon weapon(NO_WEAPON);
    Helmet helmet(NO_HELMET);
    Chestplate chestplate(false);
    players.insert_or_assign(next_player_id, PlayerDTO(next_player_id, 0, 0, true,
    State::BLANK, weapon, helmet, chestplate)); actual_players++; */

    Duck *duck = new Duck(player_id, 10 * player_id,  50 , *this);
    players.push_back(duck);
}

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

void GameMap::process_action(std::shared_ptr<Action> &action) {
    int player_id = action->get_player_id();
    Duck *duck = findPlayer(player_id);
    if (!duck)
        return;

    switch (action->get_type()) {
        case MOVE:
            duck->move(action->is_right());
            break;
        case JUMP_FLAP:
            std::cout << "Salto" << std::endl;
            duck->jump();
            break;
        case STILL:
            duck->stopMoving();
            break;
        default:
            std::cout << "Acción inválida" << std::endl;
            break;
    }
}

std::list<PlayerDTO> GameMap::getState() {
  std::list<PlayerDTO> playersList;
  for (auto player : players) {
    int id = player->getId();
    int posX = player->getPositionX();
    int posY = player->getPositionY();
    bool dir = player->getDirection();
    State state = player->getState();
    playersList.emplace_back(id, posX, posY, dir, state, WeaponDTO(NO_WEAPON), Helmet(NO_HELMET), Chestplate(false));
  }
  return playersList;
}

PlayerDTO GameMap::getPlayerState(int playerId) {
  Duck *duck = findPlayer(playerId);
  if (duck == nullptr) {
    throw std::runtime_error("Jugador no encontrado");
  }

  int id = duck->getId();
  int posX = duck->getPositionX();
  int posY = duck->getPositionY();
  bool dir = duck->getDirection();
  State state = duck->getState();

  PlayerDTO player(id, posX, posY, dir, state, WeaponDTO(NO_WEAPON), Helmet(NO_HELMET), Chestplate(false));

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

