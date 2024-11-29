#ifndef DUCK_H
#define DUCK_H

#include "server/configs/configurations.h"
#include "common/events/items/item_spawn.h" 
#include "game_map.h"
#include "weapons/weapon.h"
#include <atomic>
#include "hitBox.h"


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
  void equipWeapon(std::unique_ptr<Weapon>&& newWeapon);
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

  int shootingCooldown;

  PlayerDTO toDTO() const;
  ~Duck();

    void dropHelmet();

    void dropArmour();

    bool dropWeapon();

    bool impact(Bullet &bullet);

    void reset(int pos_x, int pos_y);
};

#endif // DUCK_H
