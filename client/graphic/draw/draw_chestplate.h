#ifndef CHESTPLATE_H
#define CHESTPLATE_H

#include "../../../common/events/items/chestplate.h"
#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>

class DrawChestplate {
private:
  std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

  SDL2pp::Renderer &renderer;

  bool equipped;

public:
  explicit DrawChestplate(SDL2pp::Renderer &renderer, bool equipped = false);

  void render(int x, int y, bool direction);

  void update(const Chestplate &chestplate);

  bool isEquipped();
};
#endif