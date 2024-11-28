#include "duck.h"
#include "server/configs/configurations.h"
#include "server/logic/weapons/ak47.h"
#include "server/logic/weapons/cowboy.h"
#include "server/logic/weapons/duelos.h"
#include "server/logic/weapons/grenade.h"
#include "server/logic/weapons/banana.h"
#include "server/logic/weapons/laser_rifle.h"
#include "server/logic/weapons/magnum.h"
#include "server/logic/weapons/no_weapon.h"
#include "server/logic/weapons/pewpewlaser.h"
#include "server/logic/weapons/shotgun.h"
#include "server/logic/weapons/sniper.h"
#include "server/logic/weapon_factory.h"
#include <iostream>

const int SPEED_X = CONFIG.getDuckConfig().getSpeedX();
const int SPEED_Y = CONFIG.getDuckConfig().getSpeedY();
const int GRAVITY = CONFIG.getDuckConfig().getGravity();
const int FLAPPING_SPEED = CONFIG.getDuckConfig().getFlappingSpeed();

const int WIDTH = CONFIG.getDuckConfig().getWidth();
const int HEIGHT = CONFIG.getDuckConfig().getHeight();
const int CENTER_X = CONFIG.getDuckConfig().getCenterX();
const int CENTER_Y = CONFIG.getDuckConfig().getCenterY();

Duck::Duck(std::atomic<int> id, int posX, int posY, GameMap &map)
    : id(id), posX(posX), posY(posY), map(map), state(State::BLANK), wins(0) {

  velX = 0;
  velY = 0;
  jumping = false;
  flapping = false;
  shooting = false;
  isRight = true;
  aimingUpwards = false;
  weapon = std::make_unique<LaserRifle>(map);
  hasWeapon = false;
  hasHelmet = false;
  hasArmour = false;
  isOnPlatform = false;

  shootingCooldown = 0;
  bananaEffectRemaining = 0;
}

void Duck::reset(int pos_x, int pos_y){
    velX = 0;
    velY = 0;
    jumping = false;
    flapping = false;
    shooting = false;
    isRight = true;
    aimingUpwards = false;
    weapon = std::make_unique<NoWeapon>(map);
    hasWeapon = false;
    hasHelmet = false;
    hasArmour = false;
    isOnPlatform = false;

    shootingCooldown = 0;
    bananaEffectRemaining = 0;

    state = State::BLANK;
    posX = pos_x;
    posY = pos_y;
}

void Duck::moveLeft() {
  velX = -SPEED_X;
  isRight = false;
  state = State::WALKING;
}

void Duck::moveRight() {
  velX = SPEED_X;
  isRight = true;
  state = State::WALKING;
}

void Duck::move(bool is_right) {
  if (is_right) {
    moveRight();
  } else {
    moveLeft();
  }
}

void Duck::jump() {
  if (!jumping) {
    velY = -SPEED_Y;
    jumping = true;
    flapping = false;
    state = State::JUMPING;
  }
}

void Duck::stopMoving() {
  velX = 0;
  state = State::BLANK;
}

void Duck::flap() {
  if (jumping && velY > 0 && !hasWeapon) {
    velY = FLAPPING_SPEED;
    flapping = true;
    state = State::FLAPPING;
  }
}

void Duck::update() {
  if (state == State::DEAD) {
    return;
  }

  shooting = shootingCooldown > 0;
  if (shooting) {
    shootingCooldown--;
  }

  if (state == State::PLAYING_DEAD) {
    velX = 0;
    velY = 0;
    return;
  }

  if (map.checkCollisionsWithBorders(id)){
    state = State::DEAD;
    return;
  }

  posX += velX;
  posY += velY;
  
  if (bananaEffectRemaining > 0) {
    bananaEffectRemaining--;
    posX += isRight ? 2 : -2;
  }else{
    posX += velX;
  }

  if ((velX < 0 && isRight) || (velX > 0 && !isRight)) {
    velX = 0;
  }

  hitBox duckBox = {posX + CENTER_X, posY + CENTER_Y, WIDTH, HEIGHT};

  isOnPlatform = false;

  for (const auto &structure : map.getMap().structures) {
    hitBox structureBox = {structure.start_x * 16, structure.y * 16,
                           (structure.end_x + 1 - structure.start_x) * 16, 16};

    if (hitBox::isColliding(duckBox, structureBox)) {
      if (velY > 0) {
        posY = structure.y * 16 - 32;
        velY = 0;
        jumping = false;
        flapping = false;
        isOnPlatform = true;

        if (state != State::AIMING_UPWARDS) {
          aimingUpwards = false;

          if (velX == 0) {
            state = State::BLANK;
          } else {
            state = State::WALKING;
          }
        }
        break;
      }
    }
  }
//Colisiones con rampas izquierdas
  for (const auto &ramp : map.getMap().leftRamps) {
    hitBox rampBox = {ramp.start_x * 16, ramp.y * 16, (ramp.end_x + 1 - ramp.start_x) * 16, 16};

    if (hitBox::isColliding(duckBox, rampBox)) {
      if (velY > 0) {
        posY = ramp.y * 16 - 24;
        velY = 0;
        jumping = false;
        flapping = false;
        isOnPlatform = true;

        if (state != State::AIMING_UPWARDS) {
          aimingUpwards = false;

          if (velX == 0) {
            state = State::BLANK;
          } else {
            state = State::WALKING;
          }
        }
        break;
      }
    }
  }

  //Colisiones con rampas derechas
  for (const auto &ramp : map.getMap().rightRamps) {
    hitBox rampBox = {ramp.start_x * 16, ramp.y * 16, (ramp.end_x + 1 - ramp.start_x) * 16, 16};

    if (hitBox::isColliding(duckBox, rampBox)) {
      if (velY > 0) {
        posY = ramp.y * 16 - 24;
        velY = 0;
        jumping = false;
        flapping = false;
        isOnPlatform = true;

        if (state != State::AIMING_UPWARDS) {
          aimingUpwards = false;

          if (velX == 0) {
            state = State::BLANK;
          } else {
            state = State::WALKING;
          }
        }
        break;
      }
    }
  }



  if (jumping || !isOnPlatform) {
    velY += flapping ? FLAPPING_SPEED : GRAVITY;

    if (state != State::AIMING_UPWARDS && jumping && velY > 0) {
      state = State::FALLING;
    }
    if (flapping){
      state = State::FLAPPING;
    }
  }
  
  if (weapon) {
    weapon->decreaseCooldown();
  }
}

void Duck::shoot() {
  if (weapon && weapon->isReadyToShoot() && state != State::PLAYING_DEAD) {
    weapon->shoot(this);
    shootingCooldown = 1;
    shooting = true;
  }
}

void Duck::equipHelmet() { hasHelmet = true; }

void Duck::equipArmour() { hasArmour = true; }

void Duck::equipWeapon(std::unique_ptr<Weapon> &&newWeapon) {
  weapon = std::move(newWeapon);
  hasWeapon = true;
}

void Duck::takeDamage() {

  if (hasHelmet) {
    hasHelmet = false;
  } else if (hasArmour) {
    hasArmour = false;
  } else {
    // muere
    state = State::DEAD;
  }
}

bool Duck::canPickUp(ItemSpawnId item) {
  if (state == State::PLAYING_DEAD) {
    return false;
  }
  if (hasHelmet && ItemSpawnId::HELMET_SPAWN == item) {
    return false;
  }
  if (hasArmour && ItemSpawnId::CHESTPLATE_SPAWN == item) {
    return false;
  }
  if(hasWeapon && ItemSpawnId::HELMET_SPAWN != item && ItemSpawnId::CHESTPLATE_SPAWN != item){
    return false;
  }
  return true;
}

void Duck::pickUp() {
  ItemSpawnId item = map.itemCollisions(id);
  if (item != ItemSpawnId::NOTHING_SPAWN) {
    if (ItemSpawnId::HELMET_SPAWN == item) {
      equipHelmet();
    } else if (ItemSpawnId::CHESTPLATE_SPAWN == item) {
      equipArmour();
    } else if (ItemSpawnId::HELMET_SPAWN != item && ItemSpawnId::CHESTPLATE_SPAWN != item) {
      auto weapon = WeaponFactory::createWeapon(item, map);
      equipWeapon(std::move(weapon));
  }
  }
}

void Duck::drop() {
  if (hasWeapon) {
    weapon = std::make_unique<NoWeapon>(map);
    hasWeapon = false;
  }
}

void Duck::playDead() {
  if (state != PLAYING_DEAD && !isFalling()) {
    state = PLAYING_DEAD;
    velX = 0;
    velY = 0;
  }
}

bool Duck::isFalling() const { return jumping || flapping; }

void Duck::aimUpwards() {
  aimingUpwards = true;
  state = State::AIMING_UPWARDS;
}

void Duck::standBack(int count) {

  if (!aimingUpwards) {
    if (isRight) {
      velX -= count;
    } else {
      velX += count;
    }
    state = State::RECOIL;
  }
}

int Duck::getPositionX() const { return posX; }

int Duck::getPositionY() const { return posY; }

int Duck::getId() const { return id; }

bool Duck::getDirection() const { return isRight; }

State Duck::getState() const { return state; }

bool Duck::isWearingHelmet() const { return hasHelmet; }

bool Duck::isWearingArmour() const { return hasArmour; }

bool Duck::isJumping() const { return jumping; }

bool Duck::isShooting() const { return shooting; }

bool Duck::isAimingUpwards() const { return aimingUpwards; }

const Weapon *Duck::getWeapon() const { return weapon.get(); }

void Duck::increaseWins() { wins++; }

PlayerDTO Duck::toDTO() const {

  return {id,
          posX,
          posY,
          isRight,
          state,
          WeaponDTO(weapon->getWeaponId(), posX, posY, isShooting()),
          HelmetDTO(hasHelmet ? KNIGHT : NO_HELMET),
          Chestplate(isWearingArmour())};
}

Duck::~Duck() {}

uint8_t Duck::getWins() const { return wins; }

void Duck::setWins() { wins = 200; }

void Duck::collideWithBanana() { bananaEffectRemaining = 100; }

// void Duck::replenishAmmo() { weapon->replenishAmmo(); }

void Duck::throwEverything() {
  weapon = std::make_unique<NoWeapon>(map);
  hasHelmet = false;
  hasWeapon = false;
  hasArmour = false;
}

void Duck::die() { state = State::DEAD;}

void Duck::replenishAmmo() {
  if (hasWeapon){
    weapon->replenishAmmo();
  }
}

/*bool Duck::impact(Bullet &bullet) {
    Position position = Position(posX, posY, WIDTH, HEIGHT);
    bool is_impact = bullet.impact(position, id);
    if (is_impact) {
        takeDamage();
    }
    return is_impact;
} */