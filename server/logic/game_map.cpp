
#include "game_map.h"
#include "common/events/player.h"
#include "explosion.h"
#include "duck.h"
#include <iostream>
#include <stdexcept>
#include <yaml-cpp/yaml.h>
#include <ctime>
#include <random>


GameMap::GameMap() : winner_id(0), rounds(0), reset(false) {
  loadMap();
}

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
    auto& spawn = map.spawns[spawn_index];

    Duck *duck = new Duck(player_id, spawn.x * 16, spawn.y * 16, *this);
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
    for (auto &crate: map.boxes) {
        crates.push_back({crate.get_hp(), crate.get_posx() *16, crate.get_posy() *16}); 
    }
}

void GameMap::addSpawnItem() {
    for (auto &itemSpawn: map.armors) {
        itemSpawns.push_back({itemSpawn.x * 16, itemSpawn.y *16, ItemSpawnId::CHESTPLATE_SPAWN, false}); 
    }
    for (auto &itemSpawn: map.helmets) {
        itemSpawns.push_back({itemSpawn.x *16, itemSpawn.y *16, ItemSpawnId::HELMET_SPAWN, false}); 
    }

    for (auto &itemSpawn: map.weaponSpawns) {
        ItemSpawnId weapon = getRandomWeapon();
        itemSpawns.push_back({itemSpawn.x *16, itemSpawn.y *16, weapon, false}); 
    }
} 

ItemSpawnId GameMap::getRandomWeapon() {
    int randomValue = std::rand() % 10 + 1;
    return static_cast<ItemSpawnId>(randomValue);
}
 
Duck *GameMap::findPlayer(int playerId) {
    for (auto player: players) {
        if (player->getId() == playerId) {
            return player;
        }
    }
    return nullptr;
}

void GameMap::update() {

    for (auto player: players) {
        if (player->getState() == State::DEAD) {
            continue;
        }

        player->update();
    }

    for (const auto &bullet: bullets) {
        bullet->update();
    }

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                 [](const std::shared_ptr<Bullet> &bullet) {
                                     return bullet->outOfRange();
                                 }),
                  bullets.end());

    //checkBulletCollisionWithPlayers();
    bulletCollisions();

    throwables.erase(std::remove_if(throwables.begin(), throwables.end(),
                                [](const std::shared_ptr<Throwable> &throwable) {
                                        return throwable->isOver();
                                    }),
                     throwables.end());

    for (const auto &throwable: throwables) {
        throwable->update();
    }

    bananaCollisions();

    for (const auto &explosion: explosions) {
        explosion->update();
    }

    for (auto &itemSpawn: itemSpawns) {
        if (!itemSpawn.isAvailable()) {
            itemSpawn.update();
        }
    }

    explosions.erase(std::remove_if(explosions.begin(), explosions.end(),
                                    [](const std::shared_ptr<Explosion> &explosion) {
                                        return explosion->isOver();
                                    }),
                     explosions.end());

    explosionCollisions();
    
    reset = false;

    bulletCollisionsWithCrates();

    if (check_players_alive()){
        reset_round();
    }
}

/*void GameMap::checkBulletCollisionWithPlayers() {
    for (auto player: players) {
        if (player->getState() == State::DEAD) {
            continue;
        }
        for (auto it = bullets.begin(); it != bullets.end();) {
            if (player->impact(**it)) {
                it = bullets.erase(it);
            } else {
                it++;
            }
        }
    }
} */

bool GameMap::checkCollisionsWithBorders(int playerId) {
    Duck *player = findPlayer(playerId);
    if (!player)
        return true;

    if (player->getPositionX() >= map.width * 16 || player->getPositionX() <= -30) {
        return true;
    }
    if (player->getPositionY() >= map.height * 16 || player->getPositionY() <= -30) {
        return true;
    }
    return false;
}

void GameMap::process_action(std::shared_ptr<Action> &action) {
    int player_id = action->get_player_id();
    Duck *duck = findPlayer(player_id);
    if (duck->getState() == State::DEAD) {
        return;
    }
    if (!duck)
        return;
        
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

std::list<BulletDTO> GameMap::getBulletsState() {
    std::list<BulletDTO> bulletsList;

    for (const auto &bullet: bullets) {
        bulletsList.emplace_back(bullet->toDTO());
    }

    return bulletsList;
}

std::list<ExplosionDTO> GameMap::getExplosionsState() {
    std::list<ExplosionDTO> explosionsList;
    for (const auto &explosion: explosions) {
        explosionsList.emplace_back(explosion->toDTO());
    }
    return explosionsList;
}

std::list<PlayerDTO> GameMap::getState() {
    std::list<PlayerDTO> playersList;
    for (auto player: players) {
        playersList.emplace_back(player->toDTO());
    }
    return playersList;
}

std::list<CrateDTO> GameMap::getCratesState() {
    std::list<CrateDTO> cratesList;
    for (auto crateIt = crates.begin(); crateIt != crates.end();) {
        cratesList.emplace_back(crateIt->toDto());
        crateIt->resetHitState();
        ++crateIt;
    }
    return cratesList;
}

std::list<ItemSpawnDTO> GameMap::getItemSpawnsState() {
    std::list<ItemSpawnDTO> itemSpawnsList;
    for (const auto &itemSpawn: itemSpawns) {
        if (itemSpawn.isAvailable()){
            itemSpawnsList.emplace_back(itemSpawn.toDTO());
        }
    } 
    return itemSpawnsList;
}

std::list<ThrowableDTO> GameMap::getThrowablesState() {
    std::list<ThrowableDTO> throwablesList;
     for (const auto &throwable: throwables) {
        throwablesList.emplace_back(throwable->toDTO());
    } 
    return throwablesList;
}

void GameMap::bulletCollisions() {

    for (const auto &player: players) {

        if (player->getState() == State::DEAD) {
            continue;
        }

        hitBox duckBox = {player->getPositionX(), player->getPositionY(), 32, 32};
        for (auto it = bullets.begin(); it != bullets.end();) {

            hitBox bulletBox = {(*it)->getPosX(), (*it)->getPosY(), 8, 1};
            if (hitBox::isColliding(duckBox, bulletBox) && player->getId() != (*it)->getOwnerId()) {

                player->takeDamage();
                it = bullets.erase(it);
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

    hitBox duckBox = {player->getPositionX(), player->getPositionY(), 32, 32};

    for (auto &spawn: itemSpawns) {
        if (!spawn.isAvailable()) {
            continue;
        }

        hitBox itemBox = {spawn.getPosX(), spawn.getPosY(), 16, 16};

        if (hitBox::isColliding(duckBox, itemBox) && player->canPickUp(spawn.getContent())) {
            spawn.notAvailable();
            return spawn.getContent();
        }
    }
    
    return item;
}

void GameMap::bulletCollisionsWithCrates() {
    std::vector<std::shared_ptr<Bullet>> bulletsToRemove;

    for (auto crateIt = crates.begin(); crateIt != crates.end();) {
        hitBox crateBox = {crateIt->get_posx(), crateIt->get_posy(), 16, 16};
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt) {
            hitBox bulletBox = {(*bulletIt)->getPosX(), (*bulletIt)->getPosY(), 8, 1};
            if (hitBox::isColliding(crateBox, bulletBox)) {
                if (crateIt->get_hp() == 0) {
                    crateIt = crates.erase(crateIt);
                    break;
                }
                crateIt->shoot();
                
                if (crateIt->get_hp() == 0) {
                    itemSpawns.push_back({crateIt->get_posx(), crateIt->get_posy(), crateIt->get_content(), true});
                    break;
                }
                
                bulletsToRemove.push_back(*bulletIt);
            }
        }

        for (auto& bullet : bulletsToRemove) {
            bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
        }
        
        bulletsToRemove.clear();

        if (crateIt != crates.end()) {
            ++crateIt;
        }

    }

}

void GameMap::explosionCollisions() {
    for (const auto &player: players) {
        if (player->getState() == State::DEAD) {
            continue;
        }
    
        hitBox duckBox = {player->getPositionX(), player->getPositionY(), 32, 32};
        for (auto it = explosions.begin(); it != explosions.end();) {
            std::vector<Duck*> &damagedPlayers=(*it)->getPlayersDamaged();
            bool damaged = false;
            for (auto damagedPlayer: damagedPlayers) {
                if (player->getId() == damagedPlayer->getId()) {
                    damaged = true;
                    break;
                }
            }
            if (damaged) {
                ++it;
                continue;
            }

            hitBox explosionBox = {(*it)->getPosX(), (*it)->getPosY(), (*it)->getRadius(), (*it)->getRadius()};
            if (hitBox::isColliding(duckBox, explosionBox)) {
                player->takeDamage();
                (*it)->addPlayerDamaged(player);
            } 
            ++it;
        }
    }
}

void GameMap::bananaCollisions() {
    for (const auto &player: players) {
        if (player->getState() == State::DEAD) {
            continue;
        }
        hitBox duckBox = {player->getPositionX(), player->getPositionY(), 32, 32};
        for (auto it = throwables.begin(); it != throwables.end();) {
            if ((*it)->getId() != THROWN_BANANA_V2) {
                ++it;
                continue;
            }
            if (!(*it)->isCollidable()) {
                ++it;
                continue;
            }

            hitBox bananaBox = {(*it)->getPosX(), (*it)->getPosY(), 8, 4};
            if (hitBox::isColliding(duckBox, bananaBox)) {
                player->collideWithBanana();
                (*it)->consume();   

            }
            ++it;
        }
    }
}

void GameMap::reapDead() {
    auto it = std::remove_if(players.begin(), players.end(), [](Duck *player) {
        if (player->getState() == State::DEAD) {
            delete player;
            return true;
        }
        return false;
    });

    players.erase(it, players.end());
}

GameMap::~GameMap() {
    for (auto player: players) {
        delete player;
    }

    for (auto &bullet: bullets) {
        bullet.reset();
    }
}

MapDTO GameMap::getMapDTO() { return mapLoader.getNextMapDTO(); }

Map GameMap::getMap() { return map; }

bool GameMap::check_players_alive() {
    int playersAlive = players.size();
    for (auto player: players) {
        if (player->getState() == State::DEAD) {
            playersAlive--;
        }
    }
    if (playersAlive == 1) {
        for (auto player: players) {
            if (player->getState() != State::DEAD) {
                player->increaseWins();
            }
        }
    }
    return playersAlive <= 1;
}

bool GameMap::check_finished(){
    if (rounds < 10){
        return false;
    }
    uint8_t maxWins = 0;
    bool draw = false;
    for (auto player: players) {
        int wins = player->getWins();
        if (wins > maxWins && wins >= 10) {
            winner_id = player->getId();
            maxWins = wins;
            draw = false;
        }
        else if (player->getWins() == maxWins){
            draw = true;
        }
    }
    if (winner_id && !draw){
        return true;
    }
    return false;
}

void GameMap::reset_round() {
    rounds++;
    reset = true;
    for (auto player: players) {
        player->reset(map.getGroundLevel() * 16);

    }
    bullets.clear();
    explosions.clear();
    crates.clear();
    throwables.clear();
    itemSpawns.clear();

    loadMap();
}

void GameMap::killAll(int duckId) {
    for (auto player: players) {
        if (player->getId() != duckId){
            player->die();
        }
    }
}

int GameMap::get_winner_id() { return winner_id; }

int GameMap::getRounds() { return rounds;}

bool GameMap::pauseForScores() {return reset && (rounds % 5) == 0;}

uint8_t GameMap::getPlayerWins(int playerId) {
    for (auto player: players) {
        if (player->getId() == playerId) {
            return player->getWins();
        }
    }
    return 0;
}

bool GameMap::isResetting(){return reset;}