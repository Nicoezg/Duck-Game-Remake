#include "duck.h"
#include "server/configs/configurations.h"
#include "server/logic/weapons/sniper.h"
#include "server/logic/weapons/magnum.h"
#include "server/logic/weapons/laser_rifle.h"
#include "server/logic/weapons/cowboy.h"
#include "server/logic/weapons/duelos.h"
#include "server/logic/weapons/grenade.h"
#include "server/logic/weapons/pewpewlaser.h"
#include "server/logic/weapons/no_weapon.h"
#include <iostream>


const int SPEED_X = CONFIG.getDuckConfig().getSpeedX();
const int SPEED_Y = CONFIG.getDuckConfig().getSpeedY();
const int GRAVITY = CONFIG.getDuckConfig().getGravity();
const int FLAPPING_SPEED = CONFIG.getDuckConfig().getFlappingSpeed();

#define GROUNDLEVEL 384

Duck::Duck(std::atomic<int> id, int posX, int posY, GameMap &map)
    : id(id), posX(posX), posY(posY), map(map), state(State::BLANK) {

  velX = 0;
  velY = 0;
  jumping = false;
  flapping = false;
  shooting = false;
  isRight = true;
  aimingUpwards = false;
  weapon = std::make_unique<Sniper>(map);
  hasWeapon = true;
  hasHelmet = true;
  hasArmour = true;
  isOnPlatform = false;

  shootingCooldown = 0;
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
    shooting = shootingCooldown > 0;
    if (shooting) {
        shootingCooldown--;
    }

    if (state == State::PLAYING_DEAD) {
        velX = 0;
        velY = 0;
        return;
    }

    posX += velX;
    posY += velY;

    if ((velX < 0 && isRight) || (velX > 0 && !isRight)) {
        velX = 0;
    }

    hitBox duckBox = {posX + 7, posY + 32, 16, 23};

    isOnPlatform = false;

    for (const auto &structure : map.getMap().structures) {
        hitBox structureBox = {structure.start_x* 16, structure.y * 16,
                                (structure.end_x + 1 - structure.start_x) * 16 , 16}; 

        if (hitBox::isColliding(duckBox, structureBox)) {
            if (velY > 0) { 
                posY = structure.y * 16 - 32; 
                velY = 0;
                jumping = false;
                flapping = false;
                isOnPlatform = true;

                if (state != State::AIMING_UPWARDS) {
                    aimingUpwards = false;
                    
                    if (velX == 0){
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

        if (state != State::AIMING_UPWARDS && jumping) {
            state = State::FALLING;
        }
    }

    if (posY + 16 >= GROUNDLEVEL) {
        posY = GROUNDLEVEL - 32;
        jumping = false;
        flapping = false;
        velY = 0;

        if (state != State::PLAYING_DEAD && state != State::AIMING_UPWARDS) {
            aimingUpwards = false;

            if (velX == 0) {
            state = State::BLANK;
            } else {
            state = State::WALKING;
        }
        }
    }

    if (weapon) {
        weapon->decreaseCooldown();
    }
}


void Duck::shoot() {
    if (weapon && weapon->isReadyToShoot()) {
        weapon->shoot(this);
        shootingCooldown = 1;
        shooting = true;
        if (!weapon->hasAmmo()){
            weapon = std::make_unique<NoWeapon>(map);
            state = State::BLANK;
            hasWeapon = false;
        }
    }
}

void Duck::equipHelmet() { hasHelmet = true; }

void Duck::equipArmour() { hasArmour = true; }

void Duck::equipWeapon(std::unique_ptr<Weapon> newWeapon) {
  weapon = std::move(newWeapon);
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

void Duck::pickUp() {
  if (!hasWeapon) {
    hasWeapon = true;
    //equipWeapon(std::make_unique<Weapon>(map));
  } else if (!hasHelmet) {
    equipHelmet();
  } else if (!hasArmour) {
    equipArmour();
  }
}

void Duck::leave() {
  // para soltar
}

void Duck::playDead() {
  if (state != PLAYING_DEAD && !isFalling()) {
    state = PLAYING_DEAD;
    velX = 0;
    velY = 0;
  }
}

bool Duck::isFalling() const { return jumping || flapping; }

void Duck::aimUpwards() 
{
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


Duck::~Duck() {}