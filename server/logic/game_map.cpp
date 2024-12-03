#include "game_map.h"
#include "common/events/player.h"
#include "duck.h"
#include "explosion.h"
#include <ctime>
#include <iostream>
#include <random>
#include <stdexcept>
#include <yaml-cpp/yaml.h>

const int TILE_SIZE = 16;

GameMap::GameMap() : winner_id(0), rounds(0), reset(false) { loadMap(); }

void GameMap::loadMap() {
  map = mapLoader.getNextMap();
  addCrate();
  addSpawnItem();
}

void GameMap::addPlayer(int player_id) {
  if (map.spawns.empty()) {
    throw std::runtime_error("No hay spawns disponibles en el mapa.");
  }

  int spawn_index = player_id % map.spawns.size();
  const auto &spawn = map.spawns[spawn_index];

  Duck *duck =
      new Duck(player_id, spawn.x * TILE_SIZE, spawn.y * TILE_SIZE, *this);
  players.push_back(duck);
}

void GameMap::addBullet(std::unique_ptr<Bullet> bullet) {
  bullets.push_back(std::move(bullet));
}

void GameMap::addThrowable(std::unique_ptr<Throwable> throwable) {
  throwables.push_back(std::move(throwable));
}

void GameMap::addExplosion(std::unique_ptr<Explosion> explosion) {
  explosions.push_back(std::move(explosion));
}

void GameMap::addCrate() {
  // cppcheck-suppress useStlAlgorithm
  for (auto &crate : map.boxes) {
    crates.push_back({crate.get_hp(), crate.get_posx() * TILE_SIZE,
                      crate.get_posy() * TILE_SIZE});
  }
}

void GameMap::addSpawnItem() {
  // cppcheck-suppress useStlAlgorithm
  for (auto &itemSpawn : map.armors) {
    itemSpawns.push_back({itemSpawn.x * TILE_SIZE, itemSpawn.y * TILE_SIZE,
                          ItemSpawnId::CHESTPLATE_SPAWN, false});
  }
  // cppcheck-suppress useStlAlgorithm
  for (auto &itemSpawn : map.helmets) {
    itemSpawns.push_back({itemSpawn.x * TILE_SIZE, itemSpawn.y * TILE_SIZE,
                          ItemSpawnId::HELMET_SPAWN, false});
  }
  // cppcheck-suppress useStlAlgorithm
  for (auto &itemSpawn : map.weaponSpawns) {
    ItemSpawnId weapon = getRandomWeapon();
    itemSpawns.push_back(
        {itemSpawn.x * TILE_SIZE, itemSpawn.y * TILE_SIZE, weapon, false});
  }
}

void GameMap::update() {

  for (auto player : players) {
    if (player->getState() == State::DEAD) {
      continue;
    }

    player->update();
  }

  for (const auto &bullet : bullets) {
    bullet->update();
  }

  bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                               [](const std::shared_ptr<Bullet> &bullet) {
                                 return bullet->outOfRange();
                               }),
                bullets.end());

  bulletCollisions();
  bulletCollisionWithPlatforms();

  throwables.erase(
      std::remove_if(throwables.begin(), throwables.end(),
                     [](const std::shared_ptr<Throwable> &throwable) {
                       return throwable->isOver();
                     }),
      throwables.end());

  for (const auto &throwable : throwables) {
    throwable->update();
  }

  bananaCollisions();

  for (const auto &explosion : explosions) {
    explosion->update();
  }

  for (auto &itemSpawn : itemSpawns) {
    if (!itemSpawn.isAvailable()) {
      itemSpawn.update();
    }
  }

  explosions.erase(
      std::remove_if(explosions.begin(), explosions.end(),
                     [](const std::shared_ptr<Explosion> &explosion) {
                       return explosion->isOver();
                     }),
      explosions.end());

  explosionCollisions();

  reset = false;
  crates.erase(
      std::remove_if(crates.begin(), crates.end(),
                     [](const Box &crate) { return crate.get_hp() == 0; }),
      crates.end());

  bulletCollisionsWithCrates();

  if (check_players_alive()) {
    reset_round();
  }
}

// colisiones

bool GameMap::checkCollisionsWithBorders(int playerId) {
  const Duck *player = findPlayer(playerId);
  if (!player)
    return true;

  if (player->getPositionX() >= map.width * TILE_SIZE ||
      player->getPositionX() <= -30) {
    return true;
  }
  if (player->getPositionY() >= map.height * TILE_SIZE) {
    return true;
  }
  return false;
}

void GameMap::bulletCollisionWithPlatforms() {
  for (const auto &bullet : bullets) {
    hitBox bulletBox = hitBox(bullet->getPosX(), bullet->getPosY(), 4, 1);

    for (const auto &structure : map.structures) {
      hitBox structureBox =
          hitBox(structure.start_x * TILE_SIZE, structure.start_y * TILE_SIZE,
                 (structure.end_x + 1 - structure.start_x) * TILE_SIZE,
                 (structure.end_y + 1 - structure.start_y) * TILE_SIZE);

      if (hitBox::isColliding(bulletBox, structureBox)) {
        bool isTopCollision = false;
        bool isHorizontalCollision = false;

        if (bullet->getPrevPosY() < structureBox.y &&
            bulletBox.y + bulletBox.height >= structureBox.y) {
          isTopCollision = true;
        } else if (bullet->getPrevPosY() >
                       structureBox.y + structureBox.height &&
                   bulletBox.y <= structureBox.y + structureBox.height) {
          isTopCollision = true;
        }
        if (bullet->getPrevPosX() < structureBox.x &&
            bulletBox.x + bulletBox.width >= structureBox.x) {
          isHorizontalCollision = true;
        } else if (bullet->getPrevPosX() >
                       structureBox.x + structureBox.width &&
                   bulletBox.x <= structureBox.x + structureBox.width) {
          isHorizontalCollision = true;
        }

        bullet->bounce(isHorizontalCollision, isTopCollision);
        break;
      }
    }
  }
}

void GameMap::bulletCollisions() {

  for (const auto &player : players) {

    if (player->getState() == State::DEAD) {
      continue;
    }

    hitBox duckBox =
        hitBox(player->getPositionX(), player->getPositionY(), 32, 32);
    for (auto it = bullets.begin(); it != bullets.end();) {

      hitBox bulletBox = hitBox((*it)->getPosX(), (*it)->getPosY(), 8, 1);
      if (hitBox::isColliding(duckBox, bulletBox) &&
          player->getId() != (*it)->getOwnerId()) {

        player->takeDamage();
        bullets.erase(it);
        break;
      } else {
        ++it;
      }
    }
  }
}

ItemSpawnId GameMap::itemCollisions(int player_id) {

  Duck *player = findPlayer(player_id);
  ItemSpawnId item = ItemSpawnId::NOTHING_SPAWN;

  hitBox duckBox =
      hitBox(player->getPositionX(), player->getPositionY(), 32, 32);

  for (auto &spawn : itemSpawns) {
    if (!spawn.isAvailable()) {
      continue;
    }

    hitBox itemBox =
        hitBox(spawn.getPosX(), spawn.getPosY(), TILE_SIZE, TILE_SIZE);

    if (hitBox::isColliding(duckBox, itemBox) &&
        player->canPickUp(spawn.getContent())) {
      spawn.notAvailable();
      return spawn.getContent();
    }
  }

  return item;
}

void GameMap::bulletCollisionsWithCrates() {
  std::vector<std::shared_ptr<Bullet>> bulletsToRemove;

  for (auto crateIt = crates.begin(); crateIt != crates.end();) {
    hitBox crateBox =
        hitBox(crateIt->get_posx(), crateIt->get_posy(), TILE_SIZE, TILE_SIZE);
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();
         ++bulletIt) {
      hitBox bulletBox =
          hitBox((*bulletIt)->getPosX(), (*bulletIt)->getPosY(), 8, 1);
      if (hitBox::isColliding(crateBox, bulletBox)) {
        crateIt->shoot();

        if (crateIt->get_hp() == 0) {
          if (crateIt->get_content() == ItemSpawnId::EXPLOSION_SPAWN) {
            addExplosion(std::make_unique<Explosion>(
                *this, crateIt->get_posx() + 8, crateIt->get_posy() + 8));
          } else {
            itemSpawns.push_back({crateIt->get_posx(), crateIt->get_posy(),
                                  crateIt->get_content(), true});
          }
          break;
        }

        bulletsToRemove.push_back(*bulletIt);
      }
    }
    for (auto &bullet : bulletsToRemove) {
      bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet),
                    bullets.end());
    }

    bulletsToRemove.clear();

    if (crateIt != crates.end()) {
      ++crateIt;
    }
  }
}

void GameMap::explosionCollisions() {
  for (const auto &player : players) {
    if (player->getState() == State::DEAD) {
      continue;
    }

    hitBox duckBox =
        hitBox(player->getPositionX(), player->getPositionY(), 32, 32);
    // cppcheck-suppress useStlAlgorithm
    for (auto it = explosions.begin(); it != explosions.end();) {
      const auto &damagedPlayers = (*it)->getPlayersDamaged();
      bool damaged = false;
      for (const auto damagedPlayer : damagedPlayers) {
        if (player->getId() == damagedPlayer->getId()) {
          damaged = true;
          break;
        }
      }
      if (damaged) {
        ++it;
        continue;
      }

      hitBox explosionBox = hitBox((*it)->getPosX(), (*it)->getPosY(),
                                   (*it)->getRadius(), (*it)->getRadius());
      if (hitBox::isColliding(duckBox, explosionBox)) {
        player->takeDamage();
        (*it)->addPlayerDamaged(player);
      }
      ++it;
    }
  }
}

void GameMap::bananaCollisions() {
  for (const auto &player : players) {
    if (player->getState() == State::DEAD) {
      continue;
    }
    hitBox duckBox =
        hitBox(player->getPositionX(), player->getPositionY(), 32, 32);
    for (auto it = throwables.begin(); it != throwables.end();) {
      if ((*it)->getId() != THROWN_BANANA_V2) {
        ++it;
        continue;
      }
      if (!(*it)->isCollidable()) {
        ++it;
        continue;
      }

      hitBox bananaBox = hitBox((*it)->getPosX(), (*it)->getPosY(), 8, 4);
      if (hitBox::isColliding(duckBox, bananaBox)) {
        player->collideWithBanana();
        (*it)->consume();
      }
      ++it;
    }
  }
}

// estados

std::list<BulletDTO> GameMap::getBulletsState() {
  std::list<BulletDTO> bulletsList;
  // cppcheck-suppress useStlAlgorithm
  for (const auto &bullet : bullets) {
    bulletsList.emplace_back(bullet->toDTO());
  }

  return bulletsList;
}

std::list<ExplosionDTO> GameMap::getExplosionsState() {
  std::list<ExplosionDTO> explosionsList;
  // cppcheck-suppress useStlAlgorithm
  for (const auto &explosion : explosions) {
    explosionsList.emplace_back(explosion->toDTO());
  }
  return explosionsList;
}

std::list<PlayerDTO> GameMap::getState() {
  std::list<PlayerDTO> playersList;
  // cppcheck-suppress useStlAlgorithm
  for (const auto player : players) {
    playersList.emplace_back(player->toDTO());
  }
  return playersList;
}

std::list<CrateDTO> GameMap::getCratesState() {
  std::list<CrateDTO> cratesList;
  // cppcheck-suppress useStlAlgorithm
  for (auto crateIt = crates.begin(); crateIt != crates.end();) {
    cratesList.emplace_back(crateIt->toDto());
    crateIt->resetHitState();
    ++crateIt;
  }
  return cratesList;
}

std::list<ItemSpawnDTO> GameMap::getItemSpawnsState() {
  std::list<ItemSpawnDTO> itemSpawnsList;
  for (const auto &itemSpawn : itemSpawns) {
    if (itemSpawn.isAvailable()) {
      itemSpawnsList.emplace_back(itemSpawn.toDTO());
    }
  }
  return itemSpawnsList;
}

std::list<ThrowableDTO> GameMap::getThrowablesState() {
  std::list<ThrowableDTO> throwablesList;
  for (const auto &throwable : throwables) {
    throwablesList.emplace_back(throwable->toDTO());
  }
  return throwablesList;
}

MapDTO GameMap::getMapDTO() { return mapLoader.getNextMapDTO(); }

Map GameMap::getMap() { return map; }

// manejo de jugadores

bool GameMap::check_players_alive() {
  int playersAlive = players.size();
  for (const auto player : players) {
    if (player->getState() == State::DEAD) {
      playersAlive--;
    }
  }
  if (playersAlive == 1) {
    for (auto player : players) {
      if (player->getState() != State::DEAD) {
        player->increaseWins();
      }
    }
  }
  return playersAlive <= 1;
}

bool GameMap::check_finished() {
  if (rounds < 10 || rounds % 5 != 0) {
    return false;
  }
  uint8_t maxWins = 0;
  bool draw = false;
  for (const auto player : players) {
    int wins = player->getWins();
    if (wins > maxWins && wins >= 10) {
      winner_id = player->getId();
      maxWins = wins;
      draw = false;
    } else if (player->getWins() == maxWins) {
      draw = true;
    }
  }
  if (winner_id && !draw) {
    return true;
  }
  return false;
}

void GameMap::reset_round() {
  rounds++;
  reset = true;

  bullets.clear();
  explosions.clear();
  crates.clear();
  throwables.clear();
  itemSpawns.clear();

  loadMap();

  for (auto player : players) {
    int id = player->getId();
    int spawn_index = id % map.spawns.size();
    const auto &spawn = map.spawns[spawn_index];
    player->reset(spawn.x * TILE_SIZE, spawn.y * TILE_SIZE);
  }
}

void GameMap::killAll(int duckId) {
  for (auto player : players) {
    if (player->getId() != duckId) {
      player->die();
    }
  }
}

int GameMap::get_winner_id() { return winner_id; }

int GameMap::getRounds() { return rounds; }

bool GameMap::pauseForScores() { return reset && (rounds % 5) == 0; }

int GameMap::getPlayerWins(int playerId) {
  for (const auto player : players) {
    if (player->getId() == playerId) {
      return player->getWins();
    }
  }
  return 0;
}

bool GameMap::isResetting() { return reset; }

// manejo de acciones

void GameMap::process_action(std::shared_ptr<Action> &action) {
  int player_id = action->get_player_id();
  Duck *duck = findPlayer(player_id);
  if (!duck)
    return;

  if (duck->getState() == State::DEAD) {
    return;
  }

  switch (action->get_type()) {
  case MOVE:
    duck->move(action->is_right());
    break;
  case JUMP_FLAP:
    if (!duck->isJumping()) {
      duck->jump();
    } else {
      duck->flap();
    }
    break;
  case STILL:
    duck->stopMoving();
    break;
  case SHOOT:
    duck->shoot();
    break;
  case PLAY_DEAD:
    duck->playDead();
    break;
  case AIM_UPWARDS:
    duck->aimUpwards();
    break;
  case PICK_DROP:
    if (action->is_picking_dropping()) {
      duck->pickUp();
    } else {
      duck->drop();
    }
    break;
  case CHEAT:
    switch (action->get_cheat_id()) {
    case 1:
      duck->equipWeapon(std::make_unique<Grenade>(*this));
      break;
    case 2:
      duck->equipWeapon(std::make_unique<Banana>(*this));
      break;
    case 3:
      duck->equipWeapon(std::make_unique<PewPewLaser>(*this));
      break;
    case 4:
      duck->equipWeapon(std::make_unique<LaserRifle>(*this));
      break;
    case 5:
      duck->equipWeapon(std::make_unique<Ak47>(*this));
      break;
    case 6:
      duck->equipWeapon(std::make_unique<Duelos>(*this));
      break;
    case 7:
      duck->equipWeapon(std::make_unique<Cowboy>(*this));
      break;
    case 8:
      duck->equipWeapon(std::make_unique<Magnum>(*this));
      break;
    case 9:
      duck->equipWeapon(std::make_unique<Shotgun>(*this));
      break;
    case 10:
      duck->equipWeapon(std::make_unique<Sniper>(*this));
      break;
    case 11:
      duck->equipHelmet();
      break;
    case 12:
      duck->equipArmour();
      break;
    case 13:
      rounds = 20;
      duck->setWins();
      break;
    case 14:
      killAll(duck->getId());
      break;
    case 15:
      duck->throwEverything();
      break;
    case 16:
      reset_round();
      break;
    case 17:
      duck->replenishAmmo();
      break;
    default:
      std::cout << "Cheat inválido" << std::endl;
      break;
    }
    break;
  default:
    std::cout << "Acción inválida" << std::endl;
    break;
  }
}

ItemSpawnId GameMap::getRandomWeapon() {
  int randomValue = std::rand() % 10 + 1;
  return static_cast<ItemSpawnId>(randomValue);
}

Duck *GameMap::findPlayer(int playerId) {
  for (auto player : players) {
    if (player->getId() == playerId) {
      return player;
    }
  }
  return nullptr;
}

GameMap::~GameMap() {
  for (auto player : players) {
    delete player;
  }

  for (auto &bullet : bullets) {
    bullet.reset();
  }
}