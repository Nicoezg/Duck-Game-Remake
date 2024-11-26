#ifndef THROWABLE_H
#define THROWABLE_H

#include "../../../common/events/items/throwable_dto.h"
#include "../sound.h"
#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>

class DrawThrowable {
private:
  SDL2pp::Renderer &renderer;

  std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

  std::map<int, std::shared_ptr<SDL2pp::Chunk>> sounds;

  Sound sound;

public:
  DrawThrowable(SDL2pp::Renderer &renderer);

  void render(const ThrowableDTO &throwable);
};
#endif