#include "draw_helmet.h"

#define DATA_PATH "../client/assets/sprites/"

DrawHelmet::DrawHelmet(SDL2pp::Renderer &renderer, HelmetId helmetId)
    : renderer(renderer), helmetId(helmetId) {
  this->textures[0] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "equipment/knight-helmet.png"));
  this->textures[1] = std::make_shared<SDL2pp::Texture>(
      renderer,
      SDL2pp::Surface(DATA_PATH "equipment/knight-helmet-equipped.png"));
}

void DrawHelmet::render(int x, int y, bool direction) {
  std::shared_ptr<SDL2pp::Texture> texture = this->textures[helmetId];
  if (direction) {
    x -= 2;
    y -= 7;
  } else {
    x += 2;
    y -= 7;
  }
  SDL2pp::Rect dest(x, y, texture->GetWidth(), texture->GetHeight());
  renderer.Copy(*texture, SDL2pp::NullOpt, dest, 0, SDL2pp::NullOpt,
                direction ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

void DrawHelmet::update(const HelmetDTO &helmet) { helmetId = helmet.get_id(); }

bool DrawHelmet::isEquipped() { return helmetId != HelmetId::NO_HELMET; }