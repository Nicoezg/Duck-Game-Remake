#include "draw_bullet.h"

#define DATA_PATH "../client/sprites/"

DrawBullet::DrawBullet(SDL2pp::Renderer &renderer) : renderer(renderer) {
  this->textures[0] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "weapons/shot.png"));
  this->textures[1] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "weapons/laser-beam.png"));
  this->textures[2] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "weapons/laser-rebound.png"));
  this->textures[3] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "weapons/grenade.png"));
  this->textures[4] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "weapons/banana-placed.png"));
}

void DrawBullet::render(const BulletDTO &bullet) {
  std::shared_ptr<SDL2pp::Texture> texture = this->textures[bullet.get_id()];
  SDL2pp::Rect dest(bullet.get_position_x(), bullet.get_position_y(),
                    texture->GetWidth(), texture->GetHeight());

  SDL_RendererFlip flip = SDL_FLIP_NONE;
  int direction = bullet.get_direction();
  if (bullet.get_direction() && bullet.get_angle() < 90) {
    flip = SDL_FLIP_HORIZONTAL;
  }
  if (direction == 1 && bullet.get_angle() > 90){
    dest.x -= 5;
  }
  else if (direction == 0 && bullet.get_angle() > 90){
    dest.x += 13;
  }

  renderer.Copy(*texture, SDL2pp::NullOpt, dest, bullet.get_angle(),
                SDL2pp::Point(), flip);
}