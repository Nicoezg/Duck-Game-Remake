#include "draw_throwable.h"

#define DATA_PATH "../client/sprites/"

DrawThrowable::DrawThrowable(SDL2pp::Renderer &renderer) : renderer(renderer), sound() {
  this->textures[0] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "weapons/grenade.png"));
  this->textures[1] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "weapons/banana-placed.png"));
  this->textures[2] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "weapons/banana-stepped.png"));

  this->sounds[0] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/grenadeFire.wav");
  this->sounds[1] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/slip.wav");
}

void DrawThrowable::render(const ThrowableDTO &throwable) {
  std::shared_ptr<SDL2pp::Texture> texture = this->textures[throwable.get_id()];
  SDL2pp::Rect dest(throwable.get_position_x(), throwable.get_position_y(),
                    texture->GetWidth(), texture->GetHeight());

  int direction = throwable.get_direction();

  renderer.Copy(*texture, SDL2pp::NullOpt, dest, throwable.get_angle(),
                SDL2pp::Point(), direction ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
  if (throwable.get_action()) {
    sound.change(this->sounds[throwable.get_id()]);
    sound.play();
  }
}