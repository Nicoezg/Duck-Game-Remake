#include "tile.h"

Tile::Tile(int start_x, int end_x, int y, int tile_id) : start_x(start_x), end_x(end_x), y(y), tile_id(tile_id) {}

int Tile::get_start_x() const {
    return start_x;
}

int Tile::get_end_x() const {
    return end_x;
}

int Tile::get_y() const {
    return y;
}

int Tile::get_tile_id() const {
    return tile_id;
}