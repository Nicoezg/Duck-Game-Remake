#include "tile.h"

Tile::Tile(int start_x, int end_x, int start_y, int end_y, int tile_id) : start_x(start_x), end_x(end_x), start_y(start_y), end_y(end_y), tile_id(tile_id) {}

int Tile::get_start_x() const {
    return start_x;
}

int Tile::get_end_x() const {
    return end_x;
}

int Tile::get_start_y() const {
    return start_y;
}

int Tile::get_end_y() const{
    return end_y;
}

int Tile::get_tile_id() const {
    return tile_id;
}