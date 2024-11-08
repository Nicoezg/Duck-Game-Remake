#include "helmet.h"
#include <memory>
#define DATA_PATH "../sprites/"

Helmet::Helmet(SDL2pp::Renderer &renderer) : renderer(renderer) {
    this->textures[0] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/helmet.png").SetColorKey(true, 0));
    this->textures[1] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/knight-helmet.png").SetColorKey(true, 0));
    this->textures[2] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/helmet-equipped.png").SetColorKey(true, 0));
    this->textures[3] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/knight-helmet-equipped.png").SetColorKey(true, 0));
}

void Helmet::render(int x, int y, int helmet_id){
    std::shared_ptr<SDL2pp::Texture> texture = this->textures[helmet_id];
    SDL2pp::Rect dest(x, y, texture->GetWidth(), texture->GetHeight());
    renderer.Copy(*texture, SDL2pp::NullOpt, dest);
}