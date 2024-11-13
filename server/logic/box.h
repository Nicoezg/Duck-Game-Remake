#include <cstdint>
#ifndef BOX_H
#define BOX_H

enum BoxItem {
  NOTHING = 0x00,
  WEAPON = 0x01,
  CHESTPLATE = 0x02,
  HELMET = 0x03
};

class Box {
private:
  int pos_x;
  int pos_y;
  uint8_t hp;
  bool is_hit;
  BoxItem content;

  BoxItem generateRandomContent();

public:
  Box(uint8_t hp, int pos_x, int pos_y);

  void shoot();
  BoxItem get_content() const;
  int get_posx() const;
  int get_posy() const;
  bool was_hit() const;
};

#endif // BOX_H
