#include "map.h"

MapDTO::MapDTO(std::list<Tile> &&platforms, int background_id, int width,
               int length)
    : Event(MAP_LOAD), platforms(std::move(platforms)),
      background_id(background_id), width(width), length(length) {}

std::list<Tile> MapDTO::get_platforms() const { return platforms; }

int MapDTO::get_background_id() const { return background_id; }

int MapDTO::get_width() const { return width; }

int MapDTO::get_length() const { return length; }