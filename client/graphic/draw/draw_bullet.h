#ifndef BULLET_H
#define BULLET_H

#include "../../../common/events/items/bullet_dto.h"
#include "../sound.h"
#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>

class DrawBullet {
private:
  std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

  SDL2pp::Renderer &renderer;

  Sound sound;

public:
  DrawBullet(SDL2pp::Renderer &renderer);

  void render(const BulletDTO &bullet);
};
#endif