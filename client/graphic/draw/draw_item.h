#ifndef SPAWN_H
#define SPAWN_H

#include "../../common/events/items/item_spawn.h"
#include "../sound.h"
#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>

class DrawItemSpawn {
private:
  std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

  SDL2pp::Renderer &renderer;

public:
  explicit DrawItemSpawn(SDL2pp::Renderer &renderer);

  void render(const ItemSpawnDTO &weapon);
};
#endif