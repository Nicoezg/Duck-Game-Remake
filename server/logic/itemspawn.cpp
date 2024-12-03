#include "itemspawn.h"
#include <iostream>

ItemSpawn::ItemSpawn(int pos_x, int pos_y, ItemSpawnId content, bool wasInBox)
    : pos_x(pos_x), pos_y(pos_y), content(content), wasInBox(wasInBox) {
  available = true;
  if (!wasInBox) {
    respawnTime = getRespawnTime();
  }
}

int ItemSpawn::getRespawnTime() const {
  int respawn = 200 + std::rand() % 301;
  return respawn;
}

int ItemSpawn::getPosX() const { return pos_x; }

int ItemSpawn::getPosY() const { return pos_y; }

bool ItemSpawn::isAvailable() const { return available; }

void ItemSpawn::update() {
  if (!available && !wasInBox) {
    respawnTime--;
    if (respawnTime == 0) {
      available = true;
      respawnTime = getRespawnTime();
    }
  }
}

ItemSpawnId ItemSpawn::getContent() const { return content; }

ItemSpawnDTO ItemSpawn::toDTO() const {
  return ItemSpawnDTO{content, pos_x, pos_y};
}

void ItemSpawn::notAvailable() { available = false; }

ItemSpawn::~ItemSpawn() {}
