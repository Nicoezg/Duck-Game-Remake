#include "box.h"

#include <cstdlib>
#include <iostream>


Box::Box(uint8_t hp, int pos_x, int pos_y)
    : pos_x(pos_x), pos_y(pos_y), hp(hp), is_hit(false) {
  content = generateRandomContent(); 
}

ItemSpawnId Box::generateRandomContent() {
  int randomValue = std::rand() % 13;
  return static_cast<ItemSpawnId>(randomValue);
}

void Box::shoot() {
  if (hp > 0) {
    hp--;
    is_hit = true;
  } 
}

CrateDTO Box::toDto() { 
  return CrateDTO{pos_x, pos_y, hp, is_hit}; ;
}

ItemSpawnId Box::get_content() const { 
  return content; 
}

void Box::resetHitState() {
    is_hit = false;
}

int Box::get_posx() const { return pos_x; }
int Box::get_posy() const { return pos_y; }
bool Box::was_hit() const { return is_hit; }
uint8_t Box::get_hp() const { return hp; }
