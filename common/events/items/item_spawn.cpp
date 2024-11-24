#include "item_spawn.h"

ItemSpawnDTO::ItemSpawnDTO(ItemSpawnId item_spawn_id, int position_x, int position_y) : item_spawn_id(item_spawn_id),
                                                                                         position_x(position_x),
                                                                                         position_y(position_y) {}

ItemSpawnId ItemSpawnDTO::get_id() const { return item_spawn_id;}

int ItemSpawnDTO::get_position_x() const { return position_x;}

int ItemSpawnDTO::get_position_y() const { return position_y;}