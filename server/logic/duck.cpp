#include "duck.h"
#include <iostream>

#define GRAVEDAD 9
#define VELOCIDAD_HORIZONTAL 10
#define VELOCIDAD_SALTO 10
#define VELOCIDAD_ALETEO 15
#define GROUNDLEVEL 10

Duck::Duck(int &id, int &posX, int &posY, GameMap &map)
    : id(id), posX(posX), posY(posY), map(map) {
  velX = 0;
  velY = 0;
  jumping = false;
  flapping = false;
  shooting = false;
  isRight = true;
  weapon = nullptr;
  state = State::BLANK;
  hasHelmet = false;
  hasArmour = false;
}

void Duck::moveLeft() {
  velX = -VELOCIDAD_HORIZONTAL;
  isRight = false;
  state = State::BLANK;
}

void Duck::moveRight() {
  velX = VELOCIDAD_HORIZONTAL;
  isRight = true;
  state = State::BLANK;
}

void Duck::move(bool isRight) {
  if (isRight) {
    moveRight();
  } else {
    moveLeft();
  }
}

void Duck::jump() {
  if (!jumping) {
    velY = -VELOCIDAD_SALTO;
    jumping = true;
    flapping = false;
    state = State::JUMPING;
  }
}

void Duck::flap() {
  if (jumping && velY > 0) {
    velY = -VELOCIDAD_ALETEO;
    flapping = true;
    state = State::BLANK;
  }
}

void Duck::update() {
  posX += velX;
  posY += velY;

  if (map.checkCollisionsWithBorders(id)) {
    posX -= velX;
    posY -= velY;
    velX = 0;
    velY = 0;
  }

  if (jumping) {
    velY += GRAVEDAD;
    state = State::FALLING;
  }

  if (posY >= GROUNDLEVEL) {
    posY = GROUNDLEVEL;
    jumping = false;
    velY = 0;
  }
}

void Duck::shoot() {
  if (weapon) {
    weapon->shoot(this);
    shooting = true;
    state = State::BLANK;
  }
}

void Duck::equipHelmet() { hasHelmet = true; }

void Duck::equipArmour() { hasArmour = true; }

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

int Duck::getPositionX() const { return posX; }

int Duck::getPositionY() const { return posY; }

int Duck::getId() const { return id; }

bool Duck::getDirection() const { return isRight; }

State Duck::getState() const { return state; }

Duck::~Duck() { delete weapon; }