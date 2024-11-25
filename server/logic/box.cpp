#include "box.h"
#include <cstdlib>
#include <iostream>

Box::Box(uint8_t hp, int pos_x, int pos_y)
    : pos_x(pos_x), pos_y(pos_y), hp(hp), is_hit(false) {
  content = generateRandomContent(); 
}

BoxItem Box::generateRandomContent() {
  int randomValue = std::rand() % 4;
  switch (randomValue) {
  case 1:
    return WEAPON;
  case 2:
    return CHESTPLATE;
  case 3:
    return HELMET;
  default:
    return NOTHING;
  }
}

void Box::shoot() {
  if (hp > 0) {
    hp--;
    if (hp == 0) {
      is_hit = true;
    }
  }
}

CrateDTO Box::toDto() { 
  return CrateDTO{pos_x, pos_y, hp, is_hit}; ;
}

BoxItem Box::get_content() const { return content; }

int Box::get_posx() const { return pos_x; }
int Box::get_posy() const { return pos_y; }
bool Box::was_hit() const { return is_hit; }
int Box::get_hp() const { return hp; }
