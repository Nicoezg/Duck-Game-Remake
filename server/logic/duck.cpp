#include "duck.h"
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

const int TILE_SIZE = 16;

Duck::Duck(std::atomic<int> id, int posX, int posY, GameMap &map)
    : id(id), posX(posX), posY(posY), velX(0), velY(0), jumping(false),
      flapping(false), shooting(false), map(map),
      weapon(std::make_unique<NoWeapon>(map)), isRight(true),
      aimingUpwards(false), state(State::BLANK), hasWeapon(false),
      hasHelmet(false), hasArmour(false), isOnPlatform(false), wins(0),
      bananaEffectRemaining(0), framesToExplode(-1), shootingCooldown(0) {}

void Duck::reset(int pos_x, int pos_y) {
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
  framesToExplode = -1;

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
  } else {
    weapon->resetConsecutiveShots();
  }

  if (state == State::PLAYING_DEAD) {
    velX = 0;
    return;
  }

  if (map.checkCollisionsWithBorders(id)) {
    state = State::DEAD;
    return;
  }

  posX += velX;
  posY += velY;

  if (bananaEffectRemaining > 0) {
    bananaEffectRemaining--;
    posX += isRight ? 2 : -2;
  } else {
    posX += velX;
  }

  if (framesToExplode == 0) {
    map.addExplosion(std::make_unique<Explosion>(map, posX, posY));
    weapon = std::make_unique<NoWeapon>(map);
    hasWeapon = false;
  }
  if (framesToExplode >= 0) {
    framesToExplode--;
  }

  if ((velX < 0 && isRight) || (velX > 0 && !isRight)) {
    velX = 0;
  }

  hitBox duckBox = hitBox(posX + CENTER_X, posY + CENTER_Y, WIDTH, HEIGHT);
  isOnPlatform = false;

  for (auto &crate : map.getCratesState()) {
    hitBox crateBox = hitBox(crate.get_position_x(), crate.get_position_y(),
                             TILE_SIZE, TILE_SIZE);

    if (hitBox::isColliding(duckBox, crateBox)) {
      if (velY > 0) {
        posY = crate.get_position_y() - TILE_SIZE * 2;
        velY = 0;
        jumping = false;
        flapping = false;
        isOnPlatform = true;

        if (state != State::AIMING_UPWARDS) {
          aimingUpwards = false;
          state = (velX == 0) ? State::BLANK : State::WALKING;
        }
        break;
      }
    }
  }

  duckBox = hitBox(posX + CENTER_X, posY + CENTER_Y, WIDTH, HEIGHT);
  for (const auto &structure : map.getMap().structures) {
    hitBox structureBox =
        hitBox(structure.start_x * TILE_SIZE, structure.start_y * TILE_SIZE,
               (structure.end_x + 1 - structure.start_x) * TILE_SIZE,
               (structure.end_y + 1 - structure.start_y) * TILE_SIZE);

    if (hitBox::isColliding(duckBox, structureBox)) {
      if (velY > 0 && structureBox.height <= 80) { // son 5 tiles
        posY = structure.start_y * TILE_SIZE - TILE_SIZE * 2;
        velY = 0;
        jumping = false;
        flapping = false;
        isOnPlatform = true;

        currentPlatformBox.x = structureBox.x;
        currentPlatformBox.y = structureBox.y;
        currentPlatformBox.width = structureBox.width;
        currentPlatformBox.height = structureBox.height;

        if (state != State::AIMING_UPWARDS) {
          aimingUpwards = false;
          state = (velX == 0) ? State::BLANK : State::WALKING;
        }
        break;
      }
    }
  }

  duckBox = hitBox(posX + CENTER_X, posY + CENTER_Y, WIDTH, HEIGHT);
  for (const auto &structure : map.getMap().structures) {
    hitBox structureBox =
        hitBox(structure.start_x * TILE_SIZE, structure.start_y * TILE_SIZE,
               (structure.end_x + 1 - structure.start_x) * TILE_SIZE,
               (structure.end_y + 1 - structure.start_y) * TILE_SIZE);

    if (hitBox::isEqual(currentPlatformBox, structureBox)) {
      continue;
    }

    if (hitBox::isColliding(duckBox, structureBox)) {

      if (velX > 0 && !jumping && !flapping) {
        posX = structureBox.x - TILE_SIZE * 2;
      } else if (velX < 0 && !jumping && !flapping) {
        posX = structureBox.x + TILE_SIZE * 2;
      }
      velX = 0;
      break;
    }
  }

  if (jumping || !isOnPlatform) {
    velY += flapping ? FLAPPING_SPEED : GRAVITY;

    currentPlatformBox.x = 0;
    currentPlatformBox.y = 0;
    currentPlatformBox.width = 0;
    currentPlatformBox.height = 0;

    if (state != State::AIMING_UPWARDS && jumping && velY > 0) {
      state = State::FALLING;
    }
    if (flapping) {
      state = State::FLAPPING;
    }
  }

  if (weapon) {
    weapon->decreaseCooldown();
  }
}

void Duck::shoot() {
  if (weapon->isReadyToShoot() && state != State::PLAYING_DEAD) {
    shooting = true;
    weapon->shoot(this);
    weapon->increaseConsecutiveShots();
    shootingCooldown = 1;
    if (weapon->getWeaponId() == WeaponId::BANANA) {
      weapon = std::make_unique<NoWeapon>(map);
      hasWeapon = false;
    }
  } else {
    weapon->reload();
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
  if (hasWeapon && ItemSpawnId::HELMET_SPAWN != item &&
      ItemSpawnId::CHESTPLATE_SPAWN != item) {
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
    } else if (ItemSpawnId::HELMET_SPAWN != item &&
               ItemSpawnId::CHESTPLATE_SPAWN != item) {
      auto pickedWeapon = WeaponFactory::createWeapon(item, map);
      equipWeapon(std::move(pickedWeapon));
    }
  }
}

void Duck::drop() {
  if (hasWeapon) {
    if (weapon->getWeaponId() == WeaponId::ARMED_GRENADE) {
      weapon->shoot(this);
    }
    weapon = std::make_unique<NoWeapon>(map);
    hasWeapon = false;
    framesToExplode = -1;
  }
}

void Duck::playDead() {
  if (state != PLAYING_DEAD && !isFalling()) {
    state = PLAYING_DEAD;
    velX = 0;
  }
}

bool Duck::isFalling() const { return jumping || flapping; }

void Duck::aimUpwards() {
  if (this->weapon->getWeaponId() == WeaponId::LASER_RIFLE) {
    return;
  }
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
          WeaponDTO(weapon->getWeaponId(), posX, posY, isShooting(),
                    weapon->hasAmmo()),
          HelmetDTO(hasHelmet ? KNIGHT : NO_HELMET),
          Chestplate(isWearingArmour())};
}

Duck::~Duck() {}

int Duck::getWins() const { return wins; }

void Duck::setWins() { wins = 200; }

void Duck::collideWithBanana() { bananaEffectRemaining = 100; }

// void Duck::replenishAmmo() { weapon->replenishAmmo(); }

void Duck::throwEverything() {
  weapon = std::make_unique<NoWeapon>(map);
  hasHelmet = false;
  hasWeapon = false;
  hasArmour = false;
}

void Duck::die() { state = State::DEAD; }

void Duck::replenishAmmo() {
  if (hasWeapon) {
    weapon->replenishAmmo();
  }
}

int Duck::getFramesToExplode() const { return framesToExplode; }

void Duck::activateGrenade() { framesToExplode = 150; }

void Duck::throwGrenade() {
  weapon = std::make_unique<NoWeapon>(map);
  hasWeapon = false;
  framesToExplode = -1;
}
