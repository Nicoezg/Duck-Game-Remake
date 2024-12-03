#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "../../../common/events/items/explosion.h"
#include "../sound.h"
#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>

class DrawExplosion {
private:
  SDL2pp::Renderer &renderer;

  std::shared_ptr<SDL2pp::Texture> texture;

  Sound sound;

  SDL2pp::Rect explosionClip[6];

public:
  explicit DrawExplosion(SDL2pp::Renderer &renderer);

  void render(const ExplosionDTO &explosion);
};
#endif