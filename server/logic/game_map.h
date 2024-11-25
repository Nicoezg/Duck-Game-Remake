#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "bullets/bullet.h"
#include "throwables/throwable.h"
#include "common/actions/base/action.h"
#include "common/events/items/bullet_dto.h"
#include "common/events/player.h"
#include "server/maploader.h"
#include <list>
#include <memory>
#include <vector>

class Duck;
class Explosion;

class GameMap {
private:
  std::vector<Duck *> players;
  std::vector<std::shared_ptr<Bullet>> bullets;
  std::vector<std::shared_ptr<Throwable>> throwables;
  std::vector<std::shared_ptr<Explosion>> explosions;
  MapLoader mapLoader;
  Map map;
  int winner_id;
  int rounds;


public:
  GameMap();

  void addPlayer(int player_id);

  void addBullet(std::unique_ptr<Bullet> bullet);

  void addThrowable(std::unique_ptr<Throwable> throwable);

  void addExplosion(std::unique_ptr<Explosion> explosion);

  Duck *findPlayer(int playerId);

  void update();

  bool checkCollisionsWithBorders(int playerId);

  PlayerDTO getPlayerState(int playerId);

  void reapDead();

  ~GameMap();

  void process_action(std::shared_ptr<Action> &action);

  std::list<PlayerDTO> getState();

  std::list<BulletDTO> getBulletsState();

  std::list<ExplosionDTO> getExplosionsState();

  std::list<CrateDTO> getCratesState();

  std::list<ItemSpawnDTO> getItemSpawnsState();

  void bulletCollisions();

  MapDTO getMapDTO();
  
  Map getMap();

    void checkBulletCollisionWithPlayers();

    bool check_players_alive();


    int get_winner_id();

    void reset_round();

    bool check_finished() const;
};

#endif
