#ifndef HELMET_H
#define HELMET_H

#include "../../../common/events/items/helmet.h"
#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>

class DrawHelmet {
private:
  std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

  SDL2pp::Renderer &renderer;

  HelmetId helmetId;

public:
  explicit DrawHelmet(SDL2pp::Renderer &renderer,
                      HelmetId helmetId = NO_HELMET);

  void render(int x, int y, bool direction = false);

  void update(const HelmetDTO &helmet);

  bool isEquipped();
};
#endif