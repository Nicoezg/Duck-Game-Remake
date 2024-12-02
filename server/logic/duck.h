#ifndef DUCK_H
#define DUCK_H

#include "../../common/configs/configurations.h"
#include "common/events/items/item_spawn.h"
#include "explosion.h"
#include "game_map.h"
#include "hitBox.h"
#include "weapons/weapon.h"
#include <atomic>

class GameMap;

class Duck {
private:
  int id;
  int posX, posY;
  int velX, velY;
  bool jumping;
  bool flapping;
  bool shooting;
  GameMap &map;
  std::unique_ptr<Weapon> weapon;
  bool isRight;
  bool aimingUpwards;
  State state;
  bool hasWeapon;
  bool hasHelmet;
  bool hasArmour;
  bool isOnPlatform;
  std::unique_ptr<Weapon> droppedWeapon;
  uint8_t wins;
  int bananaEffectRemaining;
  hitBox currentPlatformBox;
  int framesToExplode;
  int shootingCooldown;

public:
  Duck(std::atomic<int> id, int posX, int posY, GameMap &map);

  void moveRight();
  void moveLeft();
  void move(bool isRight);
  void jump();
  void flap();
  void stopMoving();
  void update();
  void resetJumpState();
  void collideWithBanana();
  hitBox getBoundingBox() const;
  bool checkCollisionWithPlatform(const Structure &platform);
  void stopAiming();
  void shoot();
  void equipHelmet();
  void equipArmour();
  void equipWeapon(std::unique_ptr<Weapon> &&newWeapon);
  void takeDamage();
  bool canPickUp(ItemSpawnId item);
  void pickUp();
  void getWeapon(ItemSpawnId item);
  void drop();
  void playDead();
  void aimUpwards();
  void standBack(int count);
  bool isAlive() const;
  int getPositionX() const;
  int getPositionY() const;
  int getId() const;
  bool getDirection() const;
  State getState() const;
  bool isWearingHelmet() const;
  bool isWearingArmour() const;
  bool isJumping() const;
  bool isShooting() const;
  bool isAimingUpwards() const;
  const Weapon *getWeapon() const;
  bool isFalling() const;
  int getWins() const;
  void increaseWins();
  void setWins();
  void replenishAmmo();
  void throwEverything();
  void die();
  int getFramesToExplode() const;
  void activateGrenade();
  void throwGrenade();

  PlayerDTO toDTO() const;
  ~Duck();

  void dropHelmet();

  void dropArmour();

  bool dropWeapon();

  void reset(int pos_x, int pos_y);
};

#endif // DUCK_H
