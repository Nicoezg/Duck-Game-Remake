#include "common/events/items/crate.h"
#include "common/events/items/item_spawn.h"
#include <cstdint>
#ifndef BOX_H
#define BOX_H

class Box {
private:
  int pos_x;
  int pos_y;
  uint8_t hp;
  bool is_hit;
  ItemSpawnId content;

  ItemSpawnId generateRandomContent();

public:
  Box(uint8_t hp, int pos_x, int pos_y);

  void shoot();
  CrateDTO toDto();
  ItemSpawnId get_content() const;
  void resetHitState();
  int get_posx() const;
  int get_posy() const;
  bool was_hit() const;
  uint8_t get_hp() const;
};

#endif // BOX_H
