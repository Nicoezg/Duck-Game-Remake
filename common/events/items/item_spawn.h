#ifndef TALLER_TP_ITEM_SPAWN_DTO_H
#define TALLER_TP_ITEM_SPAWN_DTO_H

#include "item_spawn_macros.h"
#include <string>

class ItemSpawnDTO {
private:
  ItemSpawnId item_spawn_id;
  int position_x;
  int position_y;

public:
  ItemSpawnDTO(ItemSpawnId item_spawn_id, int position_x, int position_y);

  ItemSpawnId get_id() const;

  int get_position_x() const;

  int get_position_y() const;
};

#endif // TALLER_TP_ITEM_SPAWN_DTO_H
