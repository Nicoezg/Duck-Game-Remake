#include "map.h"

Map::Map(std::vector<Tile> platforms, int background_id, int width, int length) : platforms(platforms), background_id(background_id), width(width), length(length) {}

std::vector<Tile> Map::get_platforms() const {
    return platforms;
}

int Map::get_background_id() const {
    return background_id;
}

int Map::get_width() const {
    return width;
}

int Map::get_length() const {
    return length;
}