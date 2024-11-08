#include "chestplate.h"
#include <memory>
#define DATA_PATH "../sprites/"

Chestplate::Chestplate(SDL2pp::Renderer &renderer) : renderer(renderer) {
    this->textures[0] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/chestplate.png").SetColorKey(true, 0));
    this->textures[1] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/chestplate-equipped.png").SetColorKey(true, 0));
}

void Chestplate::render(int x, int y, int chestplate_id){
    std::shared_ptr<SDL2pp::Texture> texture = this->textures[chestplate_id];
    SDL2pp::Rect dest(x, y, texture->GetWidth(), texture->GetHeight());
    renderer.Copy(*texture, SDL2pp::NullOpt, dest);
}