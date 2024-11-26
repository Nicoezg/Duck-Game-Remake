
#include "game_map.h"
#include "common/events/player.h"
#include "explosion.h"
#include "duck.h"
#include <iostream>
#include <stdexcept>
#include <yaml-cpp/yaml.h>


GameMap::GameMap() : winner_id(0), rounds(0), reset(false) {
    map = mapLoader.getNextMap();
    addCrate();
    addSpawnItem();
}

void GameMap::addPlayer(int player_id) {
    Duck *duck =
            new Duck(player_id, 10 * player_id, 384, *this);
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
        crates.push_back(crate); 
    }
}

void GameMap::addSpawnItem() {
    for (auto &itemSpawn: map.armors) {
        itemSpawns.push_back(std::make_shared<ItemSpawn>(itemSpawn.x, itemSpawn.y, ItemSpawnId::CHESTPLATE_SPAWN)); 
    }
    for (auto &itemSpawn: map.helmets) {
        itemSpawns.push_back(std::make_shared<ItemSpawn>(itemSpawn.x, itemSpawn.y, ItemSpawnId::HELMET_SPAWN)); 
    }
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

    // reapDead();
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

    explosions.erase(std::remove_if(explosions.begin(), explosions.end(),
                                    [](const std::shared_ptr<Explosion> &explosion) {
                                        return explosion->isOver();
                                    }),
                     explosions.end());

    explosionCollisions();
    

    reset = false;

    bulletCollisionsWithCrates();

    /*for (auto crate: crates) {
        if (crate.was_hit()) {
            addSpawnItem(crate.get_content(), crate.get_posx(), crate.get_posy());  
        }
    }*/

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
            duck->pickUp();
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
    for (auto crate: crates) {
        cratesList.emplace_back(crate.toDto());
    }
    return cratesList;
}


std::list<ItemSpawnDTO> GameMap::getItemSpawnsState() {
    // A implementar
    std::list<ItemSpawnDTO> itemSpawnsList;
    /* for (const auto &itemSpawn: map.getItemSpawns()) {
        itemSpawnsList.emplace_back(itemSpawn.toDTO());
    } */
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

void GameMap::bulletCollisionsWithCrates() {
    for (auto &crate: crates) {
        hitBox crateBox = {crate.get_posx(), crate.get_posy(), 16, 16};
        for (auto it = bullets.begin(); it != bullets.end();) {
            hitBox bulletBox = {(*it)->getPosX(), (*it)->getPosY(), 8, 1};
            if (hitBox::isColliding(crateBox, bulletBox)) {
                crate.shoot();
                it = bullets.erase(it);
            } else {
                ++it;
            }
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