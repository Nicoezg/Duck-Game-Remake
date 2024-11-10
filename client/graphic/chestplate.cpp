#include "chestplate.h"
#define DATA_PATH "../sprites/"

Helmet::Helmet(SDL2_pp::Renderer &renderer) : renderer(renderer) {
    this->textures[0] = SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "equipment/chestplate.png").SetColorKey(true, 0));
    this->textures[1] = SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "equipment/chestplate-equipped.png").SetColorKey(true, 0));
}

void Helmet::render(int x, int y, int chestplate_id){
    SDL2pp::Texture &texture = this->textures[chestplate_id];
    SDL2pp::Rect dest(x, y, texture.GetWidth(), texture.GetHeight());
    renderer.Copy(texture, SDL2pp::NullOpt, dest);
}