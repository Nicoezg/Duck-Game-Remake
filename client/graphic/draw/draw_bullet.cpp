#include "draw_bullet.h"
#include <cstdlib>

#define DATA_PATH "../client/assets/sprites/"

DrawBullet::DrawBullet(SDL2pp::Renderer &renderer) : renderer(renderer) {
  this->textures[0] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "weapons/shot.png"));
  this->textures[1] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "weapons/laser-beam.png"));
  this->textures[2] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "weapons/laser-rebound.png"));
}

void DrawBullet::render(const BulletDTO &bullet) {
  std::shared_ptr<SDL2pp::Texture> texture = this->textures[bullet.get_id()];
  SDL2pp::Rect dest(bullet.get_position_x(), bullet.get_position_y(),
                    texture->GetWidth(), texture->GetHeight());

  if (bullet.get_id() == BulletId::LASER_BEAM) {
    dest.w = dest.w / 2;
    dest.h = dest.h / 2;
  }

  SDL_RendererFlip flip = SDL_FLIP_NONE;
  if (bullet.get_direction()) {
    flip = SDL_FLIP_HORIZONTAL;
  }

  renderer.Copy(*texture, SDL2pp::NullOpt, dest, bullet.get_angle(),
                SDL2pp::Point(), flip);
}